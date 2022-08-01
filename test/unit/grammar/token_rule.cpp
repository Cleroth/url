//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

// Test that header file is self-contained.
#include <boost/url/grammar/token_rule.hpp>

#include <boost/url/grammar/alpha_chars.hpp>

#include "test_rule.hpp"

namespace boost {
namespace urls {
namespace grammar {

struct token_rule_test
{
    void
    run()
    {
        // test constexpr
        constexpr auto r =
            token_rule(alpha_chars);
        (void)r;
    }
};

TEST_SUITE(
    token_rule_test,
    "boost.url.grammar.token_rule");

} // grammar
} // urls
} // boost
