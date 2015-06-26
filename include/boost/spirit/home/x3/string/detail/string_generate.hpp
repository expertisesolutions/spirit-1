/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman
    Copyright (c) 2015      Felipe Magno de Almeida

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_X3_STRING_GENERATE_APR_18_2006_1125PM)
#define BOOST_SPIRIT_X3_STRING_GENERATE_APR_18_2006_1125PM

#include <boost/spirit/home/x3/support/traits/move_to.hpp>

namespace boost { namespace spirit { namespace x3 { namespace detail
{
    template <typename Char, typename OutputIterator, typename Attribute, typename CaseCompareFunc>
    inline bool string_generate(
        Char const* str
      , OutputIterator sink, Attribute const& attr, CaseCompareFunc const& compare) 
    {
        Char ch = *str;

        while (!!ch)
        {
            // if (i == last || (compare(ch, *i) != 0))
            //     return false;
            *sink++ = ch;
            ch = *++str;
        }

        return true;
    }

    template <typename String, typename OutputIterator, typename Attribute, typename CaseCompareFunc>
    inline bool string_generate(
        String const& str
      , OutputIterator sink, Attribute const& attr, CaseCompareFunc const& compare)
    {
        typename String::const_iterator stri = str.begin();
        typename String::const_iterator str_last = str.end();

        for (; stri != str_last; ++stri)
          *sink++ = stri;
            // if (i == last || (compare(*stri, *i) != 0))
            //     return false;
        return true;
    }

    // template <typename Char, typename OutputIterator, typename Attribute>
    // inline bool string_generate(
    //     Char const* uc_i, Char const* lc_i
    //   , OutputIterator& sink, OutputIterator const& last, Attribute& attr)
    // {
    //     OutputIterator i = sink;

    //     for (; *uc_i && *lc_i; ++uc_i, ++lc_i, ++i)
    //         if (i == last || ((*uc_i != *i) && (*lc_i != *i)))
    //             return false;
    //     x3::traits::move_to(sink, i, attr);
    //     sink = i;
    //     return true;
    // }

    // template <typename String, typename OutputIterator, typename Attribute>
    // inline bool string_generate(
    //     String const& ucstr, String const& lcstr
    //   , OutputIterator& sink, OutputIterator const& last, Attribute& attr)
    // {
    //     typename String::const_iterator uc_i = ucstr.begin();
    //     typename String::const_iterator uc_last = ucstr.end();
    //     typename String::const_iterator lc_i = lcstr.begin();
    //     OutputIterator i = sink;

    //     for (; uc_i != uc_last; ++uc_i, ++lc_i, ++i)
    //         if (i == last || ((*uc_i != *i) && (*lc_i != *i)))
    //             return false;
    //     x3::traits::move_to(sink, i, attr);
    //     sink = i;
    //     return true;
    // }
}}}}

#endif
