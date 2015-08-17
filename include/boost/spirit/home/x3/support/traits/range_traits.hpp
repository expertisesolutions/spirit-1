/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_X3_RANGE_FEBRUARY_06_2007_1001AM)
#define BOOST_SPIRIT_X3_RANGE_FEBRUARY_06_2007_1001AM

#include <boost/spirit/home/x3/support/traits/container_traits.hpp>

#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>

namespace boost { namespace spirit { namespace x3 { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    //  This file contains some container utils for stl containers.
    ///////////////////////////////////////////////////////////////////////////

    template <typename T, typename Enable = void>
    struct is_range
      : is_container<T>
    {};

    ///////////////////////////////////////////////////////////////////////
    template <typename Container, typename Enable = void>
    struct range_value
      : container_value<Container>
    {};

    ///////////////////////////////////////////////////////////////////////
    template <typename Range>
    struct range_value<Range const>
      : range_value<Range>
    {};
  
    ///////////////////////////////////////////////////////////////////////////
    template <typename Range, typename Enable>
    struct range_iterator
        : mpl::identity<typename Range::iterator> {};

    template <typename Range>
    struct range_iterator<Range const>
         : mpl::identity<typename Range::const_iterator> {};

    template <>
    struct range_iterator<unused_type>
        : mpl::identity<unused_type const*> {};

    template <>
    struct range_iterator<unused_type const>
        : mpl::identity<unused_type const*> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Range, typename Enable = void>
    struct begin_range
    {
        static typename range_iterator<Range>::type call(Range& c)
        {
            return std::begin(c);
        }
    };

    template <typename Range>
    inline typename range_iterator<Range>::type
    begin(Range& c)
    {
        return begin_range<Range>::call(c);
    }

    inline unused_type const*
    begin(unused_type)
    {
        return &unused;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Range, typename Enable = void>
    struct end_range
    {
        static typename range_iterator<Range>::type call(Range& c)
        {
            return std::end(c);
        }
    };

    template <typename Range>
    inline typename range_iterator<Range>::type
    end(Range& c)
    {
        return end_range<Range>::call(c);
    }

    inline unused_type const*
    end(unused_type)
    {
        return &unused;
    }
  
    // Specialization for [const] char*
    template <>
    struct is_range<const char*>
      : mpl::true_
    {};
    template <>
    struct is_range<char*>
      : mpl::true_
    {};

    template <>
    struct range_value<const char*>
    {
      typedef char type;
    };

    template <>
    struct range_value<char*> : range_value<const char*>
    {};   

    template <>
    struct range_iterator<const char*>
    {
      typedef const char* type;
    };
    template <>
    struct range_iterator<const char* const>
    {
      typedef const char* type;
    };
    template <>
    struct range_iterator<char*>
    {
      typedef char* type;
    };
    template <>
    struct range_iterator<char* const>
    {
      typedef char* type;
    };

    inline
    const char*
    begin(const char* c)
    {
        return c;
    }
    inline
    const char*
    end(const char* c)
    {
        return c + std::strlen(c);
    }

    inline
    char*
    begin(char* c)
    {
        return c;
    }
    inline
    char*
    end(char* c)
    {
        return c + std::strlen(c);
    }
  
    // inline
    // const char*
    // begin(const char* c)
    // {
    //     return c;
    // }
    // inline
    // const char*
    // end(const char* c)
    // {
    //     return c + std::strlen(c);
    // }
  
}}}}

#endif
