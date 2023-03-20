///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "task_control_block.hpp"

auto mcal::scheduler::task_control_block::execute(const mcal::scheduler::tick_type& timepoint_of_ckeck_ready) -> bool
{
  // Check for a task event.
  const auto task_does_have_event = (my_event != static_cast<event_type>(UINT8_C(0)));

  if(task_does_have_event)
  {
    // Call the task function because of an event.
    my_func();
  }

  // Check for a task timeout.
  const bool task_does_have_timeout = (   (my_cycle != static_cast<mcal::scheduler::tick_type>(UINT8_C(0)))
                                       &&  my_timer.timeout_of_specific_timepoint(timepoint_of_ckeck_ready));

  if(task_does_have_timeout)
  {
    // Increment the task's interval timer with the task cycle.
    my_timer.start_interval(my_cycle);

    // Call the task function because of a timer timeout.
    my_func();
  }

  return (task_does_have_event || task_does_have_timeout);
}