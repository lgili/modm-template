
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <cstdint>
#include <limits>
#include <src/task_list.hpp>

namespace mcal::scheduler
{
  [[noreturn]] auto start   () -> void;
              auto set_event  (const task_id_type task_id, const event_type& event_to_set) -> bool;
              auto get_event  (event_type& event_to_get) -> void;
              auto clear_event(const event_type& event_to_clear) -> void;

}


