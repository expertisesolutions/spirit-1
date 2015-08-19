/*=============================================================================
    Copyright (c) 2001-2015 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <string>
#include <vector>

#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/home/x3.hpp>

#include <string>
#include <iostream>
#include "test.hpp"

struct x_attr
{
};

namespace boost { namespace spirit { namespace x3 { namespace traits
{
    template <>
    struct container_value<x_attr>
    {
        typedef char type; // value type of container
    };

    template <>
    struct push_back_container<x_attr>
    {
        static bool call(x_attr& /*c*/, char /*val*/)
        {
            // push back value type into container
            return true;
        }
    };
}}}}

int
main()
{
    using spirit_test::test;
    using spirit_test::test_gen;
    using spirit_test::test_attr;
    using boost::spirit::x3::char_;
    using boost::spirit::x3::alpha;
    using boost::spirit::x3::upper;
    using boost::spirit::x3::space;
    using boost::spirit::x3::digit;
    using boost::spirit::x3::int_;
    using boost::spirit::x3::lexeme;

    {
        BOOST_TEST(test("aaaaaaaa", *char_));
        BOOST_TEST(test("a", *char_));
        BOOST_TEST(test("", *char_));
        BOOST_TEST(test("aaaaaaaa", *alpha));
        BOOST_TEST(!test("aaaaaaaa", *upper));
    }

    {
        BOOST_TEST(test(" a a aaa aa", *char_, space));
        BOOST_TEST(test("12345 678 9", *digit, space));
    }

    {
        std::string s;
        BOOST_TEST(test_attr("bbbb", *char_, s) && 4 == s.size() && s == "bbbb");

        s.clear();
        BOOST_TEST(test_attr("b b b b ", *char_, s, space)  && s == "bbbb");
    }

    {
        std::vector<int> v;
        BOOST_TEST(test_attr("123 456 789 10", *int_, v, space) && 4 == v.size() &&
            v[0] == 123 && v[1] == 456 && v[2] == 789 &&  v[3] == 10);
    }

    {
        std::vector<std::string> v;
        BOOST_TEST(test_attr("a b c d", *lexeme[+alpha], v, space) && 4 == v.size() &&
            v[0] == "a" && v[1] == "b" && v[2] == "c" &&  v[3] == "d");
    }

    {
        std::vector<int> v;
        BOOST_TEST(test_attr("123 456 789", *int_, v, space) && 3 == v.size() &&
            v[0] == 123 && v[1] == 456 && v[2] == 789);
    }

    { // actions
        using boost::spirit::x3::_attr;

        std::string v;
        auto f = [&](auto& ctx){ v = _attr(ctx); };

        BOOST_TEST(test("bbbb", (*char_)[f]) && 4 == v.size() &&
            v[0] == 'b' && v[1] == 'b' && v[2] == 'b' &&  v[3] == 'b');
    }

    { // more actions
        using boost::spirit::x3::_attr;

        std::vector<int> v;
        auto f = [&](auto& ctx){ v = _attr(ctx); };

        BOOST_TEST(test("123 456 789", (*int_)[f], space) && 3 == v.size() &&
            v[0] == 123 && v[1] == 456 && v[2] == 789);
    }

    { // attribute customization

        x_attr x;
        test_attr("abcde", *char_, x);
    }

    // generator
    {
        std::string s1("aaaa");
        BOOST_TEST(test_gen("aaaa", *char_, s1));

        std::string s2("");
        BOOST_TEST(test_gen("", *char_, s2));
    }

    {
        std::string s1("aaaaa");
        BOOST_TEST(test_gen("aaaaa", char_ >> *(char_ >> char_), s1));

        s1 = "a";
        BOOST_TEST(test_gen("a", char_ >> *(char_ >> char_), s1));
        s1 = "aa";
        BOOST_TEST(!test_gen("", char_ >> *(char_ >> char_), s1));
//         BOOST_TEST(test("aa", char_ << *buffer[char_ << char_] << char_, s1));
        s1 = "aaaa";
        BOOST_TEST(!test_gen("", char_ >> *(char_ >> char_), s1));
//         BOOST_TEST(test("aaaa", char_ << *buffer[char_ << char_] << char_, s1));
    }

//     {
//         using boost::spirit::karma::strict;
//         using boost::spirit::karma::relaxed;
//         using namespace boost::assign;

//         typedef std::pair<char, char> data;
//         std::vector<data> v1;
//         v1 += std::make_pair('a', 'a'), 
//               std::make_pair('b', 'b'), 
//               std::make_pair('c', 'c'), 
//               std::make_pair('d', 'd'), 
//               std::make_pair('e', 'e'), 
//               std::make_pair('f', 'f'), 
//               std::make_pair('g', 'g'); 

//         karma::rule<spirit_test::output_iterator<char>::type, data()> r;
//         r = &char_('a') << char_;

//         BOOST_TEST(test("a", r << *(r << r), v1));
//         BOOST_TEST(test("a", relaxed[r << *(r << r)], v1));
//         BOOST_TEST(!test("", strict[r << *(r << r)], v1));

//          v1 += std::make_pair('a', 'a');

//         BOOST_TEST(!test("", r << *(r << r), v1));
//         BOOST_TEST(!test("", relaxed[r << *(r << r)], v1));
//         BOOST_TEST(!test("", strict[r << *(r << r)], v1));

//          v1 += std::make_pair('a', 'a');

//         BOOST_TEST(test("aaa", r << *(r << r), v1));
//         BOOST_TEST(test("aaa", relaxed[r << *(r << r)], v1));
//         BOOST_TEST(!test("", strict[r << *(r << r)], v1));
//     }

//     {
//         using namespace boost::assign;

//         std::vector<char> v;
//         v += 'a', 'b', 'c';

//         BOOST_TEST(test("abc", *char_, v));
//         BOOST_TEST(test_delimited("a b c ", *char_, v, ' '));
//     }

//     {
//         using namespace boost::assign;

//         std::vector<int> v;
//         v += 10, 20, 30;

//         BOOST_TEST(test("102030", *int_, v));
//         BOOST_TEST(test_delimited("10, 20, 30, ", *int_, v, lit(", ")));

//         BOOST_TEST(test("10,20,30,", *(int_ << ','), v));
//         BOOST_TEST(test_delimited("10 , 20 , 30 , ", *(int_ << ','), v, lit(' ')));

// // leads to infinite loops
// //         fusion::vector<char, char> cc ('a', 'c');
// //         BOOST_TEST(test("ac", char_ << *(lit(' ') << ',') << char_, cc));
// //         BOOST_TEST(test_delimited("a c ", 
// //             char_ << *(lit(' ') << ',') << char_, cc, " "));
//     }

//     { // actions
//         using namespace boost::assign;
//         namespace phx = boost::phoenix;

//         std::vector<char> v;
//         v += 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h';

//         BOOST_TEST(test("abcdefgh", (*char_)[_1 = phx::ref(v)]));
//         BOOST_TEST(test_delimited("a b c d e f g h ", 
//             (*char_ )[_1 = phx::ref(v)], space));
//     }

//     // failing sub-generators
//     {
//         using boost::spirit::karma::strict;
//         using boost::spirit::karma::relaxed;

//         using namespace boost::assign;

//         typedef std::pair<char, char> data;
//         std::vector<data> v2;
//         v2 += std::make_pair('a', 'a'), 
//               std::make_pair('b', 'b'), 
//               std::make_pair('c', 'c'), 
//               std::make_pair('d', 'd'), 
//               std::make_pair('e', 'e'), 
//               std::make_pair('f', 'f'), 
//               std::make_pair('g', 'g');

//         karma::rule<spirit_test::output_iterator<char>::type, data()> r;

//         r = &char_('d') << char_;
//         BOOST_TEST(test("d", *r, v2));
//         BOOST_TEST(test("d", relaxed[*r], v2));
//         BOOST_TEST(test("", strict[*r], v2));

//         r = &char_('a') << char_;
//         BOOST_TEST(test("a", *r, v2));
//         BOOST_TEST(test("a", relaxed[*r], v2));
//         BOOST_TEST(test("a", strict[*r], v2));

//         r = &char_('g') << char_;
//         BOOST_TEST(test("g", *r, v2));
//         BOOST_TEST(test("g", relaxed[*r], v2));
//         BOOST_TEST(test("", strict[*r], v2));

//         r = !char_('d') << char_;
//         BOOST_TEST(test("abcefg", *r, v2));
//         BOOST_TEST(test("abcefg", relaxed[*r], v2));
//         BOOST_TEST(test("abc", strict[*r], v2));

//         r = !char_('a') << char_;
//         BOOST_TEST(test("bcdefg", *r, v2));
//         BOOST_TEST(test("bcdefg", relaxed[*r], v2));
//         BOOST_TEST(test("", strict[*r], v2));

//         r = !char_('g') << char_;
//         BOOST_TEST(test("abcdef", *r, v2));
//         BOOST_TEST(test("abcdef", relaxed[*r], v2));
//         BOOST_TEST(test("abcdef", strict[*r], v2));

//         r = &char_('A') << char_;
//         BOOST_TEST(test("", *r, v2));
//     }

//     {
//         // make sure user defined end condition is applied if no attribute
//         // is passed in
//         using namespace boost::assign;

//         std::vector<char> v;
//         v += 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h';
//         BOOST_TEST(test("[6162636465666768]", '[' << *hex[action(v)] << ']'));
//     }

//     {
//         using boost::spirit::karma::double_;

//         std::vector<A> v(1);
//         v[0].d1 = 1.0;
//         v[0].d2 = 2.0;
//         BOOST_TEST(test("A1.02.0", 'A' << *(double_ << double_), v));
//     }

    return boost::report_errors();
}
