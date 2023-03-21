// Copyright (c) 2023 Luiz Carlos Gili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.



#include <modm/processing/scheduler/scheduler.hpp>
#include "schedule.hpp"
#include "example_task.hpp"

namespace {
    modm::Scheduler scheduler;

    TestTask1 task1;
    TestTask2 task2;
}
void os::start_os(){

    scheduler.scheduleTask(task1, 25000, 100);
    scheduler.scheduleTask(task2, 200, 10);
    for(;;){
        scheduler.schedule();
    }
}