//
// Copyright (c) 2021 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_GRAMMAR_ALNUM_CHARS_HPP
#define BOOST_URL_GRAMMAR_ALNUM_CHARS_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/grammar/detail/charset.hpp>

namespace boost {
namespace urls {
namespace grammar {

/** The set of letters and digits

    @par Example
    Character sets are used with rules and the
    functions @ref find_if and @ref find_if_not.
    @code
    result< string_view > = parse( "Johnny42", token_rule( alnumchars ) );
    @endcode

    @par BNF
    @code
    ALNUM       = ALPHA / DIGIT

    ALPHA       = %x41-5A / %x61-7A
                ; A-Z / a-z

    DIGIT       = %x30-39
                ; 0-9
    @endcode

    @par Specification
    @li <a href="https://datatracker.ietf.org/doc/html/rfc5234#appendix-B.1"
        >B.1. Core Rules (rfc5234)</a>

    @see
        @ref find_if,
        @ref find_if_not,
        @ref parse,
        @ref token_rule.
*/
#ifdef BOOST_URL_DOCS
constexpr __implementation_defined__ alnum_chars;
#else
struct alnum_chars_t
{
    constexpr
    bool
    operator()(char c) const noexcept
    {
        return
            (c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z');
    }

#ifdef BOOST_URL_USE_SSE2
    char const*
    find_if(
        char const* first,
        char const* last) const noexcept
    {
        return detail::find_if_pred(
            *this, first, last);
    }

    char const*
    find_if_not(
        char const* first,
        char const* last) const noexcept
    {
        return detail::find_if_not_pred(
            *this, first, last);
    }
#endif
};

constexpr alnum_chars_t alnum_chars{};
#endif

} // grammar
} // urls
} // boost

#endif
