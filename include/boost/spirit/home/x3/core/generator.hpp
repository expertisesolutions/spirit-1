/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman
    Copyright (c) 2013 Agustin Berge
    Copyright (c) 2015 Felipe Magno de Almeida

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_X3_GENERATOR_OCTOBER_16_2008_0254PM)
#define BOOST_SPIRIT_X3_GENERATOR_OCTOBER_16_2008_0254PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/declval.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/spirit/home/x3/support/unused.hpp>
#include <boost/spirit/home/x3/support/context.hpp>
#include <boost/spirit/home/x3/support/traits/has_attribute.hpp>
#include <boost/spirit/home/x3/support/utility/sfinae.hpp>
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

    struct generator_base {};
    struct generator_id;

    template <typename Derived>
    struct generator : generator_base
    {
        typedef Derived derived_type;
        // static bool const handles_container = false;
        // static bool const is_pass_through_unary = false;
        // static bool const has_action = false;

        Derived const& derived() const
        {
            return *static_cast<Derived const*>(this);
        }

        template <typename Action>
        action<Derived, Action>
        operator[](Action f) const
        {
            return action<Derived, Action>(this->derived(), f);
        }

        template <typename Handler>
        guard<Derived, Handler>
        on_error(Handler f) const
        {
            return guard<Derived, Handler>(this->derived(), f);
        }
    };

    struct unary_category;
    struct binary_category;

    template <typename Subject, typename Derived>
    struct unary_generator : generator<Derived>
    {
        typedef unary_category category;
        typedef Subject subject_type;
        static bool const has_action = Subject::has_action;

        unary_generator(Subject subject)
            : subject(subject) {}

        unary_generator const& get_unary() const { return *this; }

        Subject subject;
    };

    template <typename Left, typename Right, typename Derived>
    struct binary_generator : generator<Derived>
    {
        typedef binary_category category;
        typedef Left left_type;
        typedef Right right_type;
        static bool const has_action =
            left_type::has_action || right_type::has_action;

        binary_generator(Left left, Right right)
            : left(left), right(right) {}

        binary_generator const& get_binary() const { return *this; }

        Left left;
        Right right;
    };

    ///////////////////////////////////////////////////////////////////////////
    // as_generator: convert a type, T, into a generator.
    ///////////////////////////////////////////////////////////////////////////
    namespace extension
    {
        namespace detail
        {
            namespace as_generator_guard
            {
                void as_spirit_generator(...);

                template<typename T, typename R =
                    decltype(as_spirit_generator(boost::declval<T const&>()))>
                struct deduce_as_generator
                {
                    typedef R type;
                    typedef typename
                        boost::remove_cv<
                            typename boost::remove_reference<R>::type
                        >::type
                    value_type;

                    static type call(T const& v)
                    {
                        return as_spirit_generator(v);
                    }
                };
                template<typename T>
                struct deduce_as_generator<T, void>
                {};
            }
            using as_generator_guard::deduce_as_generator;
        }

        template <typename T, typename Enable = void>
        struct as_generator : detail::deduce_as_generator<T> {};

        template <>
        struct as_generator<unused_type>
        {
            typedef unused_type type;
            typedef unused_type value_type;
            static type call(unused_type)
            {
                return unused;
            }
        };

        template <typename Derived>
        struct as_generator<Derived
            , typename enable_if<is_base_of<generator_base, Derived>>::type>
        {
            typedef Derived const& type;
            typedef Derived value_type;
            static type call(Derived const& p)
            {
                return p;
            }
        };

        template <typename Derived>
        struct as_generator<generator<Derived>>
        {
            typedef Derived const& type;
            typedef Derived value_type;
            static type call(generator<Derived> const& p)
            {
                return p.derived();
            }
        };
    }

    template <typename T>
    inline typename extension::as_generator<T>::type
    as_generator(T const& x)
    {
        return extension::as_generator<T>::call(x);
    }

    template <typename Derived>
    inline Derived const&
    as_generator(generator<Derived> const& p)
    {
        return p.derived();
    }
}}}

namespace boost { namespace spirit { namespace x3 { namespace traits
{
    template <typename Subject, typename Derived, typename Context>
    struct has_attribute<x3::unary_generator<Subject, Derived>, Context>
        : has_attribute<Subject, Context> {};

    template <typename Left, typename Right, typename Derived, typename Context>
    struct has_attribute<x3::binary_generator<Left, Right, Derived>, Context>
        : mpl::bool_<has_attribute<Left, Context>::value ||
                has_attribute<Right, Context>::value> {};
}}}}

#endif
