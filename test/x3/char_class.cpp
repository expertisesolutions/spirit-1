/*=============================================================================
    Copyright (c) 2001-2015 Joel de Guzman
    Copyright (c) 2001-2010 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// this file intentionally contains non-ascii characters
// boostinspect:noascii

#define BOOST_SPIRIT_X3_UNICODE

#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/type_traits/is_same.hpp>

#include <iostream>
#include "test.hpp"
#include "test_gen.hpp"

int
main()
{
    using spirit_test::test;
    using spirit_test::test_gen;
    using spirit_test::test_attr;

    using boost::spirit::x3::unused_type;

    {
        using namespace boost::spirit::x3::ascii;
        BOOST_TEST(test("1", alnum));
        BOOST_TEST(!test(" ", alnum));
        BOOST_TEST(!test("1", alpha));
        BOOST_TEST(test("x", alpha));
        BOOST_TEST(test(" ", blank));
        BOOST_TEST(!test("x", blank));
        BOOST_TEST(test("1", digit));
        BOOST_TEST(!test("x", digit));
        BOOST_TEST(test("a", lower));
        BOOST_TEST(!test("A", lower));
        BOOST_TEST(test("!", punct));
        BOOST_TEST(!test("x", punct));
        BOOST_TEST(test(" ", space));
        BOOST_TEST(test("\n", space));
        BOOST_TEST(test("\r", space));
        BOOST_TEST(test("\t", space));
        BOOST_TEST(test("A", upper));
        BOOST_TEST(!test("a", upper));
        BOOST_TEST(test("A", xdigit));
        BOOST_TEST(test("0", xdigit));
        BOOST_TEST(test("f", xdigit));
        BOOST_TEST(!test("g", xdigit));
    }

    {
        using namespace boost::spirit::x3::ascii;
        BOOST_TEST(!test("1", ~alnum));
        BOOST_TEST(test(" ", ~alnum));
        BOOST_TEST(test("1", ~alpha));
        BOOST_TEST(!test("x", ~alpha));
        BOOST_TEST(!test(" ", ~blank));
        BOOST_TEST(test("x", ~blank));
        BOOST_TEST(!test("1", ~digit));
        BOOST_TEST(test("x", ~digit));
        BOOST_TEST(!test("a", ~lower));
        BOOST_TEST(test("A", ~lower));
        BOOST_TEST(!test("!", ~punct));
        BOOST_TEST(test("x", ~punct));
        BOOST_TEST(!test(" ", ~space));
        BOOST_TEST(!test("\n", ~space));
        BOOST_TEST(!test("\r", ~space));
        BOOST_TEST(!test("\t", ~space));
        BOOST_TEST(!test("A", ~upper));
        BOOST_TEST(test("a", ~upper));
        BOOST_TEST(!test("A", ~xdigit));
        BOOST_TEST(!test("0", ~xdigit));
        BOOST_TEST(!test("f", ~xdigit));
        BOOST_TEST(test("g", ~xdigit));
    }

    {
        using namespace boost::spirit::x3::iso8859_1;
        BOOST_TEST(test("1", alnum));
        BOOST_TEST(!test(" ", alnum));
        BOOST_TEST(!test("1", alpha));
        BOOST_TEST(test("x", alpha));
        BOOST_TEST(test(" ", blank));
        BOOST_TEST(!test("x", blank));
        BOOST_TEST(test("1", digit));
        BOOST_TEST(!test("x", digit));
        BOOST_TEST(test("a", lower));
        BOOST_TEST(!test("A", lower));
        BOOST_TEST(test("!", punct));
        BOOST_TEST(!test("x", punct));
        BOOST_TEST(test(" ", space));
        BOOST_TEST(test("\n", space));
        BOOST_TEST(test("\r", space));
        BOOST_TEST(test("\t", space));
        BOOST_TEST(test("A", upper));
        BOOST_TEST(!test("a", upper));
        BOOST_TEST(test("A", xdigit));
        BOOST_TEST(test("0", xdigit));
        BOOST_TEST(test("f", xdigit));
        BOOST_TEST(!test("g", xdigit));

// needed for VC7.1 only
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("german")
#endif
        BOOST_TEST(test("é", alpha));
        BOOST_TEST(test("é", lower));
        BOOST_TEST(!test("é", upper));
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("")
#endif
    }

    {
        using namespace boost::spirit::x3::ascii;
        BOOST_TEST(test("1", alnum));
        BOOST_TEST(!test(" ", alnum));
        BOOST_TEST(!test("1", alpha));
        BOOST_TEST(test("x", alpha));
        BOOST_TEST(test(" ", blank));
        BOOST_TEST(!test("x", blank));
        BOOST_TEST(test("1", digit));
        BOOST_TEST(!test("x", digit));
        BOOST_TEST(test("a", lower));
        BOOST_TEST(!test("A", lower));
        BOOST_TEST(test("!", punct));
        BOOST_TEST(!test("x", punct));
        BOOST_TEST(test(" ", space));
        BOOST_TEST(test("\n", space));
        BOOST_TEST(test("\r", space));
        BOOST_TEST(test("\t", space));
        BOOST_TEST(test("A", upper));
        BOOST_TEST(!test("a", upper));
        BOOST_TEST(test("A", xdigit));
        BOOST_TEST(test("0", xdigit));
        BOOST_TEST(test("f", xdigit));
        BOOST_TEST(!test("g", xdigit));
    }

    {
        using namespace boost::spirit::x3::standard_wide;
        BOOST_TEST(test(L"1", alnum));
        BOOST_TEST(!test(L" ", alnum));
        BOOST_TEST(!test(L"1", alpha));
        BOOST_TEST(test(L"x", alpha));
        BOOST_TEST(test(L" ", blank));
        BOOST_TEST(!test(L"x", blank));
        BOOST_TEST(test(L"1", digit));
        BOOST_TEST(!test(L"x", digit));
        BOOST_TEST(test(L"a", lower));
        BOOST_TEST(!test(L"A", lower));
        BOOST_TEST(test(L"!", punct));
        BOOST_TEST(!test(L"x", punct));
        BOOST_TEST(test(L" ", space));
        BOOST_TEST(test(L"\n", space));
        BOOST_TEST(test(L"\r", space));
        BOOST_TEST(test(L"\t", space));
        BOOST_TEST(test(L"A", upper));
        BOOST_TEST(!test(L"a", upper));
        BOOST_TEST(test(L"A", xdigit));
        BOOST_TEST(test(L"0", xdigit));
        BOOST_TEST(test(L"f", xdigit));
        BOOST_TEST(!test(L"g", xdigit));
    }

    {
        using namespace boost::spirit::x3::unicode;
        BOOST_TEST(test(L"1", alnum));
        BOOST_TEST(!test(L" ", alnum));
        BOOST_TEST(!test(L"1", alpha));
        BOOST_TEST(test(L"x", alpha));
        BOOST_TEST(test(L" ", blank));
        BOOST_TEST(!test(L"x", blank));
        BOOST_TEST(test(L"1", digit));
        BOOST_TEST(!test(L"x", digit));
        BOOST_TEST(test(L"a", lower));
        BOOST_TEST(!test(L"A", lower));
        BOOST_TEST(test(L"!", punct));
        BOOST_TEST(!test(L"x", punct));
        BOOST_TEST(test(L" ", space));
        BOOST_TEST(test(L"\n", space));
        BOOST_TEST(test(L"\r", space));
        BOOST_TEST(test(L"\t", space));
        BOOST_TEST(test(L"A", upper));
        BOOST_TEST(!test(L"a", upper));
        BOOST_TEST(test(L"A", xdigit));
        BOOST_TEST(test(L"0", xdigit));
        BOOST_TEST(test(L"f", xdigit));
        BOOST_TEST(!test(L"g", xdigit));

        BOOST_TEST(test(L"A", alphabetic));
        BOOST_TEST(test(L"9", decimal_number));
        BOOST_TEST(test(L"\u2800", braille));
        BOOST_TEST(!test(L" ", braille));
        BOOST_TEST(test(L" ", ~braille));
        // $$$ TODO $$$ Add more unicode tests

// needed for VC7.1 only
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("german")
#endif
        BOOST_TEST(test("é", alpha));
        BOOST_TEST(test("é", lower));
        BOOST_TEST(!test("é", upper));

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("")
#endif
    }

    {   // test attribute extraction
        using boost::spirit::x3::traits::attribute_of;
        using boost::spirit::x3::iso8859_1::alpha;
        using boost::spirit::x3::iso8859_1::alpha_type;

        static_assert(
            boost::is_same<
                attribute_of<alpha_type, unused_type>::type
              , unsigned char>::value
          , "Wrong attribute type!"
        );

        int attr = 0;
        BOOST_TEST(test_attr("a", alpha, attr));
        BOOST_TEST(attr == 'a');
    }

    {   // test attribute extraction
        using boost::spirit::x3::iso8859_1::alpha;
        using boost::spirit::x3::iso8859_1::space;
        char attr = 0;
        BOOST_TEST(test_attr("     a", alpha, attr, space));
        BOOST_TEST(attr == 'a');
    }

    {   // test action
        using namespace boost::spirit::x3::ascii;
        using boost::spirit::x3::_attr;
        char ch;
        auto f = [&](auto& ctx){ ch = _attr(ctx); };

        BOOST_TEST(test("x", alnum[f]));
        BOOST_TEST(ch == 'x');
        BOOST_TEST(test("   A", alnum[f], space));
        BOOST_TEST(ch == 'A');
    }

    // generators
    {
        using namespace boost::spirit::x3::ascii;
        BOOST_TEST(test_gen("a", alpha, 'a'));
        BOOST_TEST(!test_gen("", alpha, '1'));
        BOOST_TEST(test_gen(" ", blank, ' '));
        BOOST_TEST(!test_gen("", blank, 'x'));
        BOOST_TEST(test_gen("1", digit, '1'));
        BOOST_TEST(!test_gen("", digit, 'x'));
        BOOST_TEST(test_gen("a", lower, 'a'));
        BOOST_TEST(!test_gen("", lower, 'A'));
        BOOST_TEST(test_gen("!", punct, '!'));
        BOOST_TEST(!test_gen("", punct, 'x'));
        BOOST_TEST(!test_gen(" ", space));
        BOOST_TEST(test_gen(" ", space, ' '));
        BOOST_TEST(!test_gen("", space, '\n'));
        BOOST_TEST(test_gen("\r", space, '\r'));
        BOOST_TEST(test_gen("\t", space, '\t'));
        BOOST_TEST(test_gen("A", upper, 'A'));
        BOOST_TEST(!test_gen("", upper, 'a'));
        BOOST_TEST(test_gen("A", xdigit, 'A'));
        BOOST_TEST(test_gen("0", xdigit, '0'));
        BOOST_TEST(test_gen("f", xdigit, 'f'));
        BOOST_TEST(!test_gen("", xdigit, 'g'));
    }

    {
        using namespace boost::spirit::x3::ascii;
        BOOST_TEST(!test_gen("", ~alpha, 'a'));
        BOOST_TEST(test_gen("1", ~alpha, '1'));
        BOOST_TEST(!test_gen("", ~blank, ' '));
        BOOST_TEST(test_gen("x", ~blank, 'x'));
        BOOST_TEST(!test_gen("", ~digit, '1'));
        BOOST_TEST(test_gen("x", ~digit, 'x'));
        BOOST_TEST(!test_gen("", ~lower, 'a'));
        BOOST_TEST(test_gen("A", ~lower, 'A'));
        BOOST_TEST(!test_gen("", ~punct, '!'));
        BOOST_TEST(test_gen("x", ~punct, 'x'));
        BOOST_TEST(!test_gen("", ~space));
        BOOST_TEST(!test_gen("", ~space, ' '));
        BOOST_TEST(!test_gen("", ~space, '\r'));
        BOOST_TEST(!test_gen("", ~space, '\t'));
        BOOST_TEST(!test_gen("", ~upper, 'A'));
        BOOST_TEST(test_gen("a", ~upper, 'a'));
        BOOST_TEST(!test_gen("", ~xdigit, 'A'));
        BOOST_TEST(!test_gen("", ~xdigit, '0'));
        BOOST_TEST(!test_gen("", ~xdigit, 'f'));
        BOOST_TEST(test_gen("g", ~xdigit, 'g'));
    }

    {
        using namespace boost::spirit::x3::ascii;
        BOOST_TEST(test_gen("a", ~~alpha, 'a'));
        BOOST_TEST(!test_gen("", ~~alpha, '1'));
        BOOST_TEST(test_gen(" ", ~~blank, ' '));
        BOOST_TEST(!test_gen("", ~~blank, 'x'));
        BOOST_TEST(test_gen("1", ~~digit, '1'));
        BOOST_TEST(!test_gen("", ~~digit, 'x'));
        BOOST_TEST(test_gen("a", ~~lower, 'a'));
        BOOST_TEST(!test_gen("", ~~lower, 'A'));
        BOOST_TEST(test_gen("!", ~~punct, '!'));
        BOOST_TEST(!test_gen("", ~~punct, 'x'));
        BOOST_TEST(!test_gen(" ", ~~space));
        BOOST_TEST(test_gen(" ", ~~space, ' '));
        BOOST_TEST(!test_gen("", ~~space, '\n'));
        BOOST_TEST(test_gen("\r", ~~space, '\r'));
        BOOST_TEST(test_gen("\t", ~~space, '\t'));
        BOOST_TEST(test_gen("A", ~~upper, 'A'));
        BOOST_TEST(!test_gen("", ~~upper, 'a'));
        BOOST_TEST(test_gen("A", ~~xdigit, 'A'));
        BOOST_TEST(test_gen("0", ~~xdigit, '0'));
        BOOST_TEST(test_gen("f", ~~xdigit, 'f'));
        BOOST_TEST(!test_gen("", ~~xdigit, 'g'));
    }

    {
        using namespace boost::spirit::x3::iso8859_1;
        BOOST_TEST(test_gen("a", alpha, 'a'));
        BOOST_TEST(!test_gen("", alpha, '1'));
        BOOST_TEST(test_gen(" ", blank, ' '));
        BOOST_TEST(!test_gen("", blank, 'x'));
        BOOST_TEST(test_gen("1", digit, '1'));
        BOOST_TEST(!test_gen("", digit, 'x'));
        BOOST_TEST(test_gen("a", lower, 'a'));
        BOOST_TEST(!test_gen("", lower, 'A'));
        BOOST_TEST(test_gen("!", punct, '!'));
        BOOST_TEST(!test_gen("", punct, 'x'));
        BOOST_TEST(!test_gen(" ", space));
        BOOST_TEST(test_gen(" ", space, ' '));
        BOOST_TEST(!test_gen("", space, '\n'));
        BOOST_TEST(test_gen("\r", space, '\r'));
        BOOST_TEST(test_gen("\t", space, '\t'));
        BOOST_TEST(test_gen("A", upper, 'A'));
        BOOST_TEST(!test_gen("", upper, 'a'));
        BOOST_TEST(test_gen("A", xdigit, 'A'));
        BOOST_TEST(test_gen("0", xdigit, '0'));
        BOOST_TEST(test_gen("f", xdigit, 'f'));
        BOOST_TEST(!test_gen("", xdigit, 'g'));


// needed for VC7.1 only
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("german")
#endif
        BOOST_TEST(test_gen("é", alpha, 'é'));
        BOOST_TEST(test_gen("é", lower, 'é'));
        BOOST_TEST(!test_gen("", upper, 'é'));
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
#pragma setlocale("")
#endif
    }

    {
      using namespace boost::spirit::x3::standard;
        BOOST_TEST(test_gen("a", alpha, 'a'));
        BOOST_TEST(!test_gen("", alpha, '1'));
        BOOST_TEST(test_gen(" ", blank, ' '));
        BOOST_TEST(!test_gen("", blank, 'x'));
        BOOST_TEST(test_gen("1", digit, '1'));
        BOOST_TEST(!test_gen("", digit, 'x'));
        BOOST_TEST(test_gen("a", lower, 'a'));
        BOOST_TEST(!test_gen("", lower, 'A'));
        BOOST_TEST(test_gen("!", punct, '!'));
        BOOST_TEST(!test_gen("", punct, 'x'));
        BOOST_TEST(!test_gen(" ", space));
        BOOST_TEST(test_gen(" ", space, ' '));
        BOOST_TEST(!test_gen("", space, '\n'));
        BOOST_TEST(test_gen("\r", space, '\r'));
        BOOST_TEST(test_gen("\t", space, '\t'));
        BOOST_TEST(test_gen("A", upper, 'A'));
        BOOST_TEST(!test_gen("", upper, 'a'));
        BOOST_TEST(test_gen("A", xdigit, 'A'));
        BOOST_TEST(test_gen("0", xdigit, '0'));
        BOOST_TEST(test_gen("f", xdigit, 'f'));
        BOOST_TEST(!test_gen("", xdigit, 'g'));
    }

    {
        using namespace boost::spirit::x3::standard_wide;
        BOOST_TEST(test_gen(L"a", alpha, L'a'));
        BOOST_TEST(!test_gen(L"", alpha, L'1'));
        BOOST_TEST(test_gen(L" ", blank, L' '));
        BOOST_TEST(!test_gen(L"", blank, L'x'));
        BOOST_TEST(test_gen(L"1", digit, L'1'));
        BOOST_TEST(!test_gen(L"", digit, L'x'));
        BOOST_TEST(test_gen(L"a", lower, L'a'));
        BOOST_TEST(!test_gen(L"", lower, L'A'));
        BOOST_TEST(test_gen(L"!", punct, L'!'));
        BOOST_TEST(!test_gen(L"", punct, L'x'));
        BOOST_TEST(!test_gen(L" ", space));
        BOOST_TEST(test_gen(L" ", space, L' '));
        BOOST_TEST(!test_gen(L"", space, L'\n'));
        BOOST_TEST(test_gen(L"\r", space, L'\r'));
        BOOST_TEST(test_gen(L"\t", space, L'\t'));
        BOOST_TEST(test_gen(L"A", upper, L'A'));
        BOOST_TEST(!test_gen(L"", upper, L'a'));
        BOOST_TEST(test_gen(L"A", xdigit, L'A'));
        BOOST_TEST(test_gen(L"0", xdigit, L'0'));
        BOOST_TEST(test_gen(L"f", xdigit, L'f'));
        BOOST_TEST(!test_gen(L"", xdigit, L'g'));
    }
    
    return boost::report_errors();
}
