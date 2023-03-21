// Copyright (c) 2023 Luiz Carlos Gili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#pragma once 
#include <mcal/board.hpp>
#include <modm/processing/scheduler/scheduler.hpp>

// ----------------------------------------------------------------------------


class TestTask1 : public modm::Scheduler::Task
{
public:
	TestTask1() :
		order(0)
	{
	}

	virtual void
	run()
	{
		Board::Leds::toggle();
		//MODM_LOG_INFO << "task 1" << modm::endl;
	}

	uint8_t order;
};

class TestTask2 : public modm::Scheduler::Task
{
public:
	TestTask2() :
		order(0)
	{
	}

	virtual void
	run()
	{

		//MODM_LOG_INFO << "task 2" << modm::endl;
	}

	uint8_t order;
};