/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_X3_GENERATE_APRIL_16_2006_0442PM)
#define BOOST_SPIRIT_X3_GENERATE_APRIL_16_2006_0442PM

#include <boost/spirit/home/x3/support/context.hpp>
#include <boost/spirit/home/x3/core/generator.hpp>
#include <boost/spirit/home/x3/core/skip_over.hpp>
#include <boost/concept_check.hpp>

namespace boost { namespace spirit { namespace x3
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Generator, typename Attribute>
    inline bool
    generate_main(
        OutputIterator sink
      , Generator const& p
      , Attribute const& attr)
    {
        // If you get an error no matching function for call to 'as_generator'
        // here, then p is not a generator or there is no suitable conversion
        // from p to a generator.
        return as_generator(p).generate(sink, unused, unused, attr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Generator, typename Attribute>
    inline bool
    generate(
        OutputIterator sink
      , Generator const& p
      , Attribute const& attr)
    {
        return generate_main(sink, p, attr);
    }

    // ///////////////////////////////////////////////////////////////////////////
    // template <typename Iterator, typename Generator, typename Attribute>
    // inline bool
    // generate(
    //     Iterator const& first_
    //   , Iterator last
    //   , Generator const& p
    //   , Attribute& attr)
    // {
    //     Iterator first = first_;
    //     return generate_main(first, last, p, attr);
    // }

    // ///////////////////////////////////////////////////////////////////////////
    // template <typename Iterator, typename Generator>
    // inline bool
    // generate(
    //     Iterator& first
    //   , Iterator last
    //   , Generator const& p)
    // {
    //     return generate_main(first, last, p, unused);
    // }

    // ///////////////////////////////////////////////////////////////////////////
    // template <typename Iterator, typename Generator>
    // inline bool
    // generate(
    //     Iterator const& first_
    //   , Iterator last
    //   , Generator const& p)
    // {
    //     Iterator first = first_;
    //     return generate_main(first, last, p, unused);
    // }

    // ///////////////////////////////////////////////////////////////////////////
    // template <typename OutputIterator, typename Generator, typename Skipper, typename Attribute>
    // inline bool
    // phrase_generate_main(
    //     OutputIterator first
    //   , Generator const& p
    //   , Skipper const& s
    //   , Attribute& attr
    //   , skip_flag post_skip = skip_flag::post_skip)
    // {
    //     // Make sure the iterator is at least a forward_iterator. If you got a
    //     // compilation error here, then you are using an input_iterator while
    //     // calling this function. You need to supply at least a forward_iterator
    //     // instead.
    //     BOOST_CONCEPT_ASSERT((ForwardIterator<Iterator>));

    //     // If you get an error no matching function for call to 'as_generator'
    //     // here, for either p or s, then p or s is not a generator or there is
    //     // no suitable conversion from p to a generator.
    //     auto skipper_ctx = make_context<skipper_tag>(as_generator(s));
    //     bool r = as_generator(p).generate(first, last, skipper_ctx, unused, attr);
    //     if (post_skip == skip_flag::post_skip)
    //         x3::skip_over(first, last, skipper_ctx);
    //     return r;
    // }

    // ///////////////////////////////////////////////////////////////////////////
    // template <typename Iterator, typename Generator, typename Skipper, typename Attribute>
    // inline bool
    // phrase_generate(
    //     Iterator& first
    //   , Iterator last
    //   , Generator const& p
    //   , Skipper const& s
    //   , Attribute& attr
    //   , skip_flag post_skip = skip_flag::post_skip)
    // {
    //     return phrase_generate_main(first, last, p, s, attr, post_skip);
    // }

    // ///////////////////////////////////////////////////////////////////////////
    // template <typename Iterator, typename Generator, typename Skipper, typename Attribute>
    // inline bool
    // phrase_generate(
    //     Iterator const& first_
    //   , Iterator last
    //   , Generator const& p
    //   , Skipper const& s
    //   , Attribute& attr
    //   , skip_flag post_skip = skip_flag::post_skip)
    // {
    //     Iterator first = first_;
    //     return phrase_generate_main(first, last, p, s, attr, post_skip);
    // }

    // ///////////////////////////////////////////////////////////////////////////
    // template <typename Iterator, typename Generator, typename Skipper>
    // inline bool
    // phrase_generate(
    //     Iterator& first
    //   , Iterator last
    //   , Generator const& p
    //   , Skipper const& s
    //   , skip_flag post_skip = skip_flag::post_skip)
    // {
    //     return phrase_generate_main(first, last, p, s, unused, post_skip);
    // }

    // ///////////////////////////////////////////////////////////////////////////
    // template <typename Iterator, typename Generator, typename Skipper>
    // inline bool
    // phrase_generate(
    //     Iterator const& first_
    //   , Iterator last
    //   , Generator const& p
    //   , Skipper const& s
    //   , skip_flag post_skip = skip_flag::post_skip)
    // {
    //     Iterator first = first_;
    //     return phrase_generate_main(first, last, p, s, unused, post_skip);
    // }
    
    // ///////////////////////////////////////////////////////////////////////////
    // template <typename Skipper>
    // struct phrase_generate_context
    // {
    //     typedef decltype(
    //         make_context<skipper_tag>(as_generator(std::declval<Skipper>())))
    //     type;
    // };
}}}

#endif
