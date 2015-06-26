/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman
    Copyright (c) 2013 Agustin Berge
    Copyright (c) 2015 Felipe Magno de Almeida

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_X3_BOTH_OCTOBER_16_2008_0254PM)
#define BOOST_SPIRIT_X3_BOTH_OCTOBER_16_2008_0254PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/x3/core/parser.hpp>
#include <boost/spirit/home/x3/core/generator.hpp>
#include <string>

#if !defined(BOOST_SPIRIT_X3_NO_RTTI)
#include <typeinfo>
#endif

namespace boost { namespace spirit { namespace x3
{
    using x3::unused_type;
    using x3::unused;
    using x3::get;

    template <typename Subject, typename Action>
    struct action;

    template <typename Subject, typename Handler>
    struct guard;

    struct both_base {};
    struct both_id;

    ///////////////////////////////////////////////////////////////////////////
    // as_generator: convert a type, T, into a generator.
    ///////////////////////////////////////////////////////////////////////////
    namespace extension
    {

        template <typename T, typename Enable = void>
        struct as_both;

        template <>
        struct as_both<unused_type>
        {
            typedef unused_type type;
            typedef unused_type value_type;
            static type call(unused_type)
            {
                return unused;
            }
        };

        template <typename Derived>
        struct as_both<Derived
                       , /*typename enable_if_c
                           <is_base_of<generator_base, Derived>::value && is_base_of<parser_base, Derived>::value>::type*/void>
        {
            typedef Derived const& type;
            typedef Derived value_type;
            static type call(Derived const& p)
            {
                return p;
            }
        };
    }

    template <typename T>
    inline typename extension::as_both<T>::type
    as_both(T const& x)
    {
        return extension::as_both<T>::call(x);
    }

    // template <typename Derived>
    // inline Derived const&
    // as_both(generator<Derived> const& p)
    // {
    //     return p.derived();
    // }
}}}

namespace boost { namespace spirit { namespace x3 { namespace traits
{
    // template <typename Subject, typename Derived, typename Context>
    // struct has_attribute<x3::unary_both<Subject, Derived>, Context>
    //     : has_attribute<Subject, Context> {};

    // template <typename Left, typename Right, typename Derived, typename Context>
    // struct has_attribute<x3::binary_both<Left, Right, Derived>, Context>
    //     : mpl::bool_<has_attribute<Left, Context>::value ||
    //             has_attribute<Right, Context>::value> {};
}}}}

#endif
