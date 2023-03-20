///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <array>
#include <iterator>


#include "scheduler.hpp"
#include "task_control_block.hpp"
#include <modm/architecture/interface/atomic_lock.hpp>	

namespace local
{
  using task_list_type  = std::array<mcal::scheduler::task_control_block, TASK_COUNT>;

  using task_index_type = std::uint_fast8_t;

  // The one (and only one) operating system task list.
  task_list_type task_list(TASK_LIST); // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cert-err58-cpp)

  // The index of the running task.
  task_index_type task_index; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
} // namespace local



[[noreturn]] auto mcal::scheduler::start() -> void
{
  // Initialize each task once (and only once) before the task scheduling begins.
  const auto it_init_func = std::for_each(local::task_list.cbegin(),
                                          local::task_list.cend(),
                                          [](const task_control_block& the_tcb)
                                          {
                                            the_tcb.initialize();
                                          });

  static_cast<void>(it_init_func);

  // Initialize the idle task.
  IDLE_TASK_INIT();

  // Enter the endless loop of the multitasking scheduler...
  // ...and never return.
  for(;;)
  {
    // Find the next ready task using a priority-based search algorithm.
    // Use a constant time-point based on the timer mark of now.
    // In this way, each task in the loop will be checked for being
    // ready using the same time-point.

    const mcal::scheduler::tick_type timepoint_of_ckeck_ready = mcal::scheduler::timer_type::get_mark();

    local::task_index = static_cast<local::task_index_type>(0U);

    const auto it_ready_task = // NOLINT(llvm-qualified-auto,readability-qualified-auto)
      std::find_if(local::task_list.begin(),
                   local::task_list.end(),
                   [&timepoint_of_ckeck_ready](task_control_block& tcb) // NOLINT(modernize-use-trailing-return-type)
                   {
                     const auto task_is_ready = tcb.execute(timepoint_of_ckeck_ready);

                     ++local::task_index;

                     return task_is_ready;
                   });

    // If no ready-task was found, then service the idle task.
    if(it_ready_task == local::task_list.end())
    {
      IDLE_TASK_FUNC();
    }
  }
}

auto mcal::scheduler::set_event(const task_id_type task_id, const event_type& event_to_set) -> bool
{
  bool result_set_is_ok { };

  if(task_id < task_id_type::task_id_end)
  {
    // Get the iterator of the control block corresponding to
    // the task id that has been supplied to this subroutine.
    const auto it_task_id = (  local::task_list.begin() // NOLINT(llvm-qualified-auto,readability-qualified-auto)
                             + static_cast<local::task_list_type::size_type>(task_id));

    // Set the event of the corresponding task.
    modm::atomic::Lock();

    it_task_id->my_event |= event_to_set;
   
    modm::atomic::Unlock();

    result_set_is_ok = true;
  }

  return result_set_is_ok;
}

auto mcal::scheduler::get_event(event_type& event_to_get) -> void
{
  // Get the iterator of the control block of the running task.
  const auto it_running_task = (local::task_list.cbegin() + local::task_index); // NOLINT(llvm-qualified-auto,readability-qualified-auto)

  if(it_running_task != local::task_list.cend())
  {
    // Get the event of the running task.
    modm::atomic::Lock();

    const volatile event_type the_event = it_running_task->my_event;

    modm::atomic::Unlock();

    event_to_get = the_event;
  }
  else
  {
    event_to_get = event_type { };
  }
}

auto mcal::scheduler::clear_event(const event_type& event_to_clear) -> void
{
  // Get the iterator of the control block of the running task.
  const auto it_running_task = (local::task_list.begin() + local::task_index); // NOLINT(llvm-qualified-auto,readability-qualified-auto)

  if(it_running_task != local::task_list.end())
  {
    volatile const auto event_clear_mask = static_cast<event_type>(~event_to_clear);

    // Clear the event of the running task.
    modm::atomic::Lock();

    it_running_task->my_event = static_cast<event_type>(it_running_task->my_event & event_clear_mask);

    modm::atomic::Unlock();
  }
}