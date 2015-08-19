/*=============================================================================
    Copyright (c) 2001-2015 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2011      Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "int.hpp"
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>

int
main()
{
    using spirit_test::test;
    using spirit_test::test_gen;
    using spirit_test::test_attr;

    ///////////////////////////////////////////////////////////////////////////
    //  signed integer tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::x3::int_;
        int i;

        BOOST_TEST(test("123456", int_));
        BOOST_TEST(test_attr("123456", int_, i));
        BOOST_TEST(i == 123456);

        BOOST_TEST(test("+123456", int_));
        BOOST_TEST(test_attr("+123456", int_, i));
        BOOST_TEST(i == 123456);

        BOOST_TEST(test("-123456", int_));
        BOOST_TEST(test_attr("-123456", int_, i));
        BOOST_TEST(i == -123456);

        BOOST_TEST(test(max_int, int_));
        BOOST_TEST(test_attr(max_int, int_, i));
        BOOST_TEST(i == INT_MAX);

        BOOST_TEST(test(min_int, int_));
        BOOST_TEST(test_attr(min_int, int_, i));
        BOOST_TEST(i == INT_MIN);

        BOOST_TEST(!test(int_overflow, int_));
        BOOST_TEST(!test_attr(int_overflow, int_, i));
        BOOST_TEST(!test(int_underflow, int_));
        BOOST_TEST(!test_attr(int_underflow, int_, i));

        BOOST_TEST(!test("-", int_));
        BOOST_TEST(!test_attr("-", int_, i));

        BOOST_TEST(!test("+", int_));
        BOOST_TEST(!test_attr("+", int_, i));

        // Bug report from Steve Nutt
        BOOST_TEST(!test_attr("5368709120", int_, i));

        // with leading zeros
        BOOST_TEST(test("0000000000123456", int_));
        BOOST_TEST(test_attr("0000000000123456", int_, i));
        BOOST_TEST(i == 123456);
    }

    ///////////////////////////////////////////////////////////////////////////
    //  long long tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::x3::long_long;
        boost::long_long_type ll;

        BOOST_TEST(test("1234567890123456789", long_long));
        BOOST_TEST(test_attr("1234567890123456789", long_long, ll));
        BOOST_TEST(ll == 1234567890123456789LL);

        BOOST_TEST(test("-1234567890123456789", long_long));
        BOOST_TEST(test_attr("-1234567890123456789", long_long, ll));
        BOOST_TEST(ll == -1234567890123456789LL);

        BOOST_TEST(test(max_long_long, long_long));
        BOOST_TEST(test_attr(max_long_long, long_long, ll));
        BOOST_TEST(ll == LLONG_MAX);

        BOOST_TEST(test(min_long_long, long_long));
        BOOST_TEST(test_attr(min_long_long, long_long, ll));
        BOOST_TEST(ll == LLONG_MIN);

        BOOST_TEST(!test(long_long_overflow, long_long));
        BOOST_TEST(!test_attr(long_long_overflow, long_long, ll));
        BOOST_TEST(!test(long_long_underflow, long_long));
        BOOST_TEST(!test_attr(long_long_underflow, long_long, ll));
    }

    ///////////////////////////////////////////////////////////////////////////
    //  short_ and long_ tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::x3::short_;
        using boost::spirit::x3::long_;
        int i;

        BOOST_TEST(test("12345", short_));
        BOOST_TEST(test_attr("12345", short_, i));
        BOOST_TEST(i == 12345);

        BOOST_TEST(test("1234567890", long_));
        BOOST_TEST(test_attr("1234567890", long_, i));
        BOOST_TEST(i == 1234567890);
    }

    ///////////////////////////////////////////////////////////////////////////
    // Check overflow is parse error
    ///////////////////////////////////////////////////////////////////////////
    {
        boost::spirit::x3::int_parser<boost::int8_t> int8_;
        char c;

        BOOST_TEST(!test_attr("999", int8_, c));

        int i;
        using boost::spirit::x3::short_;
        BOOST_TEST(!test_attr("32769", short_, i, false));
        BOOST_TEST(!test_attr("41234", short_, i, false));
    }

    ///////////////////////////////////////////////////////////////////////////
    //  int_parser<unused_type> tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::x3::int_parser;
        using boost::spirit::x3::unused_type;
        int_parser<unused_type> any_int;

        BOOST_TEST(test("123456", any_int));
        BOOST_TEST(test("-123456", any_int));
        BOOST_TEST(test("-1234567890123456789", any_int));
    }

    ///////////////////////////////////////////////////////////////////////////
    //  action tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::x3::_attr;
        using boost::spirit::x3::ascii::space;
        using boost::spirit::x3::int_;
        int n, m;

        auto f = [&](auto& ctx){ n = _attr(ctx); };

        BOOST_TEST(test("123", int_[f]));
        BOOST_TEST(n == 123);
        BOOST_TEST(test_attr("789", int_[f], m));
        BOOST_TEST(n == 789 && m == 789);
        BOOST_TEST(test("   456", int_[f], space));
        BOOST_TEST(n == 456);
    }

    ///////////////////////////////////////////////////////////////////////////
    //  custom int tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::x3::int_;
        using boost::spirit::x3::int_parser;
        custom_int i;

        BOOST_TEST(test_attr("-123456", int_, i));
        int_parser<custom_int, 10, 1, 2> int2;
        BOOST_TEST(test_attr("-12", int2, i));
    }

    ///////////////////////////////////////////////////////////////////////////
    //  single-element fusion vector tests
    ///////////////////////////////////////////////////////////////////////////
    {
        using boost::spirit::x3::int_;
        using boost::spirit::x3::int_parser;
        boost::fusion::vector<int> i;

        BOOST_TEST(test_attr("-123456", int_, i));
        BOOST_TEST(boost::fusion::at_c<0>(i) == -123456);
    }

    // Generator
    {
        using namespace boost::spirit::x3::ascii;
        using boost::spirit::x3::int_;

        ///////////////////////////////////////////////////////////////////////
        // this is currently ambiguous with character literals
        // BOOST_TEST(test_gen("0", 0));
        // BOOST_TEST(test_gen("123", 123));
        // BOOST_TEST(test_gen("-123", -123));

        BOOST_TEST(test_gen("0", int_, 0));
        BOOST_TEST(test_gen("123", int_, 123));
        BOOST_TEST(test_gen("-123", int_, -123));

        ///////////////////////////////////////////////////////////////////////
        // BOOST_TEST(test_gen("0", int_(0)));
        // BOOST_TEST(test_gen("123", int_(123)));
        // BOOST_TEST(test_gen("-123", int_(-123)));

    }

    {   // literals, make sure there are no ambiguities
        using boost::spirit::x3::int_;
        using boost::spirit::x3::lit;

//         BOOST_TEST(test("0", lit(short(0))));
//         BOOST_TEST(test("0", lit(0)));
//         BOOST_TEST(test("0", lit(0L)));
// #ifdef BOOST_HAS_LONG_LONG
//         BOOST_TEST(test("0", lit(0LL)));
// #endif

//         BOOST_TEST(test("0", lit((unsigned short)0)));
//         BOOST_TEST(test("0", lit(0U)));
//         BOOST_TEST(test("0", lit(0UL)));
// #ifdef BOOST_HAS_LONG_LONG
//         BOOST_TEST(test("0", lit(0ULL)));
// #endif

        BOOST_TEST(test("a", lit('a')));
        BOOST_TEST(test("a", 'a'));
        BOOST_TEST(test(L"a", L'a'));
    }

    // {   // lazy numerics
    //     using namespace boost::phoenix;

    //     BOOST_TEST(test("0", int_(val(0))));
    //     BOOST_TEST(test("123", int_(val(123))));
    //     BOOST_TEST(test("-123", int_(val(-123))));

    //     int i1 = 0, i2 = 123, i3 = -123;
    //     BOOST_TEST(test("0", int_(ref(i1))));
    //     BOOST_TEST(test("123", int_(ref(i2))));
    //     BOOST_TEST(test("-123", int_(ref(i3))));
    // }
    
    {
        using namespace boost::spirit::x3::ascii;
        using boost::spirit::x3::uint_;
        using boost::spirit::x3::hex;
        using boost::spirit::x3::oct;
        using boost::spirit::x3::bin;
        
        ///////////////////////////////////////////////////////////////////////
        // BOOST_TEST(test_gen("1234", uint_(1234)));
        // BOOST_TEST(test_gen("ff", hex(0xff)));
        // BOOST_TEST(test_gen("1234", oct(01234)));
        // BOOST_TEST(test_gen("11110000", bin(0xf0)));

        BOOST_TEST(test_gen("1234", uint_, 1234));
        BOOST_TEST(test_gen("ff", hex, 0xff));
        BOOST_TEST(test_gen("1234", oct, 01234));
        BOOST_TEST(test_gen("11110000", bin, 0xf0));
    }

    return boost::report_errors();
}
