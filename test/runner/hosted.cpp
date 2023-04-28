// Copyright (c) 2023 Luiz Carlos Gili
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_DEFAULT_REPORTER "verbose" // NOLINT

#include "catch2/VerboseReporter.hpp"

#include <catch2/catch.hpp>

#include <cstdlib>
// NOLINTNEXTLINE
int main(int argc, char* argv[])
{

#ifdef TEST_TAGS
    (void) argc;

    std::array<char*, 2> argvTags{};
    argvTags[0] = argv[0];
    argvTags[1] = const_cast<char*>(TEST_TAGS);

    return Catch::Session().run(argvTags.size(), argvTags.data());
#else
    return Catch::Session().run(argc, argv);
#endif
}



