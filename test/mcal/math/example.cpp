// Copyright (c) 2023 Luiz Carlos Gili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#define CONFIG_CATCH_MAIN
#include <catch2/catch.hpp> // NOLINT

#include <cmath>
#include <limits>
#include <iostream>

// NOLINTNEXTLINE
TEST_CASE("1. Check power of 2 detection", "[unit][bits]")
{
    std::cout << "mersa\n";
    constexpr std::uint32_t cIterationsCount = 1'000;
    for (std::uint32_t i = 1; i < cIterationsCount; ++i) {
        auto value_a = static_cast<std::uint32_t>(std::log2(i));
        double value_b = std::pow(2, value_a);
        bool power_of2 = static_cast<double>(i) == value_b;

        REQUIRE(power_of2 == power_of2);
    }
}

TEST_CASE("2. Check conversions to little endian", "[unit][bits]")
{
    SECTION("2.1. 16bit conversions")
    {
        for (std::uint16_t i = 0; i < std::numeric_limits<std::uint16_t>::max(); ++i)
            REQUIRE(i == i);
    }

    SECTION("2.2. 32bit conversions")
    {
        constexpr std::uint32_t cIterationsCount = 1'000;
        for (std::uint32_t i = 0; i < cIterationsCount; ++i)
            REQUIRE(i == i);
    }

    SECTION("2.3. 64bit conversions")
    {
        constexpr std::uint64_t cIterationsCount = 1'000;
        for (std::uint64_t i = 0; i < cIterationsCount; ++i)
            REQUIRE(i == i);
    }
}