// Copyright (c) 2023 Luiz Carlos Gili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cstddef>
#include <cstdint>
#include <limits>

#include <mcal/processing/timer/timer.hpp>


// Declare the task initialization and the task function of the idle process.
namespace sys
{
  namespace idle
  {
    void task_init();
    void task_func();
  }
}

// Define symbols for the task initialization and the task function of the idle process.
#define IDLE_TASK_INIT() sys::idle::task_init()
#define IDLE_TASK_FUNC() sys::idle::task_func()

// Declare/include all of the task initializations and the task functions here.
namespace app { namespace led       { auto task_init() -> void; auto task_func() -> void; } }

namespace mcal::scheduler
{
  // Enumerate the task IDs. Note that the order in this list must
  // be identical with the order of the tasks in the task list below.
  typedef enum enum_task_id
  {
    task_id_app_led,
    task_id_end
  } task_id_type;

  // Configure the operating system types.
  using function_type = void(*)();

  using timer_type = mcal::processing::timer<std::uint_fast32_t>;
  using tick_type  = timer_type::tick_type;
  using event_type = std::uint_fast16_t;

  static_assert(std::numeric_limits<mcal::scheduler::tick_type>::digits >= 32,
                "The operating system timer_type must be at least 32-bits wide.");

  static_assert(std::numeric_limits<mcal::scheduler::event_type>::digits >= 16,
                "The operating system event_type must be at least 16-bits wide.");
}

// Configure the operating system tasks.

// Use small prime numbers (representing microseconds) for task offsets.
// Use Wolfram's Alpha or Mathematica(R): Table[Prime[n], {n, 25, 1000, 25}]
// to obtain:
//    97,  229,  379,  541,  691,  863, 1039, 1223, 1427, 1583, 1777,
//  1987, 2153, 2357, 2557, 2741, 2953, 3181, 3371, 3571, 3769, 3989,
//  4201, 4409, 4637, 4831, 5039, 5279, 5483, 5693, 5881, 6133, 6337,
//  6571, 6793, 6997, 7237, 7499, 7687, 7919

#define TASK_COUNT static_cast<std::size_t>(mcal::scheduler::task_id_end)

#define TASK_LIST                                                               \
  {                                                                             \
    {                                                                           \
      mcal::scheduler::task_control_block(app::led::task_init,                  \
                    app::led::task_func,                                        \
                    mcal::scheduler::timer_type::microseconds(UINT32_C(33334)), \
                    mcal::scheduler::timer_type::microseconds(UINT32_C(0))),    \
    }                                                                           \
  }

static_assert(TASK_COUNT > std::size_t(0U), "the task count must exceed zero");

