///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once 

#include <cstddef>
#include <cstdint>
#include <limits>
#include "scheduler.hpp"

namespace mcal::scheduler
{
  class task_control_block final
    {
    public:
      task_control_block(const function_type init,
                         const function_type func,
                         const tick_type cycle,
                         const tick_type offset)  noexcept
        : my_init (init),
          my_func (func),
          my_cycle(cycle),
          my_timer(offset),
          my_event() { }

      task_control_block(const task_control_block& other_tcb) noexcept
        : my_init (other_tcb.my_init),
          my_func (other_tcb.my_func),
          my_cycle(other_tcb.my_cycle),
          my_timer(other_tcb.my_timer),
          my_event(other_tcb.my_event) { }

      task_control_block(task_control_block&& other_tcb) noexcept
        : my_init (other_tcb.my_init),
          my_func (other_tcb.my_func),
          my_cycle(other_tcb.my_cycle),
          my_timer(other_tcb.my_timer),
          my_event(other_tcb.my_event) { }

      task_control_block() = delete;

      ~task_control_block() = default;

      auto operator=(const task_control_block&) -> task_control_block& = delete;
      auto operator=(task_control_block&&) noexcept -> task_control_block& = delete;

    private:
      const function_type my_init;
      const function_type my_func;
      const tick_type     my_cycle;
            timer_type    my_timer;
            event_type    my_event;

      auto initialize() const -> void { my_init(); }

      auto execute(const tick_type& timepoint_of_ckeck_ready) -> bool;

      friend auto start      () -> void;
      friend auto set_event  (const task_id_type, const event_type&) -> bool;
      friend auto get_event  (event_type&) -> void;
      friend auto clear_event(const event_type&) -> void;
    };
}

