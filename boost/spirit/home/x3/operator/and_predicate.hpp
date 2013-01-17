/*=============================================================================
    Copyright (c) 2001-2012 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(SPIRIT_AND_PREDICATE_MARCH_23_2007_0617PM)
#define SPIRIT_AND_PREDICATE_MARCH_23_2007_0617PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/x3/core/parser.hpp>

namespace boost { namespace spirit { namespace x3
{
    template <typename Subject>
    struct and_predicate : unary_parser<Subject, and_predicate<Subject>>
    {
        typedef unary_parser<Subject, and_predicate<Subject>> base_type;

        typedef unused_type attribute_type;
        static bool const has_attribute = false;

        and_predicate(Subject const& subject)
          : base_type(subject) {}

        template <typename Iterator, typename Context, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Attribute& /*attr*/) const
        {
            Iterator i = first;
            return this->subject.parse(i, last, context, unused);
        }
    };

    template <typename Subject>
    inline and_predicate<typename extension::as_parser<Subject>::value_type>
    operator&(Subject const& subject)
    {
        typedef
            and_predicate<typename extension::as_parser<Subject>::value_type>
        result_type;

        return result_type(as_parser(subject));
    }
}}}

#endif
