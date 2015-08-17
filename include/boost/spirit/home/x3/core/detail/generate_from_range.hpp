/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(SPIRIT_GENERATE_INTO_RANGE_JAN_15_2013_0957PM)
#define SPIRIT_GENERATE_INTO_RANGE_JAN_15_2013_0957PM

#include <type_traits>

#include <boost/spirit/home/x3/support/traits/container_traits.hpp>
#include <boost/spirit/home/x3/support/traits/range_traits.hpp>
#include <boost/spirit/home/x3/support/traits/range_traits.hpp>
#include <boost/spirit/home/x3/support/traits/value_traits.hpp>
#include <boost/spirit/home/x3/support/traits/attribute_of.hpp>
#include <boost/spirit/home/x3/support/traits/handles_container.hpp>
#include <boost/spirit/home/x3/support/traits/has_attribute.hpp>
#include <boost/spirit/home/x3/support/traits/is_substitute.hpp>
#include <boost/spirit/home/x3/support/traits/move_to.hpp>
#include <boost/mpl/and.hpp>
#include <boost/fusion/include/front.hpp>
#include <boost/fusion/include/back.hpp>
#include <boost/variant/apply_visitor.hpp>

namespace boost { namespace spirit { namespace x3 { namespace detail
{
//     // template <typename Attribute, typename Value>
//     // struct saver_visitor;

//     // // save to associative fusion range where Key is simple type
//     // template <typename Key, typename Enable = void>
//     // struct save_to_assoc_attr
//     // {
//     //     template <typename Value, typename Attribute>
//     //     static void call(const Key, Value& value, Attribute& attr)
//     //     {
//     //         traits::move_to(value, fusion::at_key<Key>(attr));
//     //     }
//     // };

// /*	$$$ clang reports: warning: class template partial specialization contains
//  *	a template parameter that can not be deduced; this partial specialization
//  *	will never be used $$$
//  *
//     // save to associative fusion range where Key
//     // is variant over possible keys
//     template <typename ...T>
//     struct save_to_assoc_attr<variant<T...> >
//     {
//         typedef variant<T...> variant_t;

//         template <typename Value, typename Attribute>
//         static void call(const variant_t key, Value& value, Attribute& attr)
//         {
//             apply_visitor(saver_visitor<Attribute, Value>(attr, value), key);
//         }
//     };
// */
//     // template <typename Attribute, typename Value>
//     // struct saver_visitor  : boost::static_visitor<void>
//     // {
//     //     saver_visitor(Attribute& attr, Value& value)
//     //         : attr(attr), value(value) {};

//     //     Attribute& attr;
//     //     Value& value;

//     //     template <typename Key>
//     //     void operator()(Key) const
//     //     {
//     //         save_to_assoc_attr<Key>::call(Key(), value,attr);
//     //     }
//     // };

//     template <typename Generator, typename Range, typename Context>
//     struct generator_accepts_range
//         : traits::is_substitute<
//                 typename traits::attribute_of<Generator, Context>::type
//               , Range
//             >
//     {};

//     template <typename Generator>
//     struct generate_from_range_base_impl
//     {
//     private:

//         // Generator has attribute (synthesize; Attribute is a range)
//         template <typename OutputIterator, typename Context
//           , typename RContext, typename Attribute>
//         static bool call_synthesize_x(
//             Generator const& generator
//           , OutputIterator sink
//           , Context const& context, RContext& rcontext, Attribute& attr, mpl::false_)
//         {
//             // synthesized attribute needs to be value initialized
//             typedef typename
//                 traits::range_value<Attribute>::type
//             value_type;
//             value_type val = traits::value_initialize<value_type>::call();

//             if (!generator.generate(sink, context, rcontext, val))
//                 return false;

//             // push the generated value from our attribute
//             traits::push_back(attr, val);
//             return true;
//         }

//         // Generator has attribute (synthesize; Attribute is a range)
//         template <typename OutputIterator, typename Context
//           , typename RContext, typename Attribute>
//         static bool call_synthesize_x(
//             Generator const& generator
//           , OutputIterator sink
//           , Context const& context, RContext& rcontext, Attribute& attr, mpl::true_)
//         {
//             return generator.generate(sink, context, rcontext, attr);
//         }

//         // Generator has attribute (synthesize; Attribute is a range)
//         template <typename OutputIterator, typename Context
//           , typename RContext, typename Attribute>
//         static bool call_synthesize(
//             Generator const& generator
//           , OutputIterator sink
//           , Context const& context, RContext& rcontext, Attribute& attr)
//         {
//             typedef
//                 generator_accepts_range<Generator, Attribute, Context>
//             generator_accepts_range;

//             return call_synthesize_x(generator, sink, context, rcontext, attr
//                 , generator_accepts_range());
//         }

//         // Generator has attribute (synthesize; Attribute is a single element fusion sequence)
//         template <typename OutputIterator, typename Context
//           , typename RContext, typename Attribute>
//         static bool call_synthesize_from_fusion_seq(Generator const& generator
//           , OutputIterator sink, Context const& context
//           , RContext& rcontext, Attribute& attr, mpl::false_ /* is_associative */)
//         {
//             static_assert(traits::has_size<Attribute, 1>::value,
//                 "Expecting a single element fusion sequence");
//             return call_synthesize(generator, sink, context, rcontext,
//                 fusion::front(attr));
//         }

//         // Generator has attribute (synthesize; Attribute is fusion map sequence)
//         template <typename OutputIterator, typename Context, typename RContext, typename Attribute
//                   , typename Iterator>
//         static bool call_synthesize_from_fusion_seq(
//             Generator const& generator
//           , OutputIterator sink, Context const& context
//           , RContext& rcontext, Attribute& attr, Iterator iterator, mpl::true_ /*is_associative*/)
//         {
//             // using attribute_type = typename traits::attribute_of<Generator, Context>::type;
//             // static_assert(traits::has_size<attribute_type, 2>::value,
//             //     "To generate directly from fusion map generator must produce 2 element attr");

//             // // use type of  sink element of attribute as key
//             // using key = typename std::remove_reference<
//             // typename fusion::result_of::front<attribute_type>::type>::type;

//             return generator.generate(sink, context, rcontext, attr_, *iterator);
//         }

//         template <typename OutputIterator, typename Context, typename RContext, typename Attribute, typename Iterator>
//         static bool call_synthesize_dispatch_by_seq(Generator const& generator
//           , OutputIterator sink, Context const& context
//           , RContext& rcontext, Attribute& attr, Iterator iterator, mpl::true_ /*is_sequence*/)
//         {
//             return call_synthesize_from_fusion_seq(
//               generator, sink, context, rcontext, attr, iterator
//               , fusion::traits::is_associative<Attribute>());
//         }

//         template <typename OutputIterator, typename Context, typename RContext, typename Attribute, typename Iterator>
//         static bool call_synthesize_dispatch_by_seq(Generator const& generator
//           , OutputIterator sink, Context const& context
//           , RContext& rcontext, Attribute& attr, Iterator iterator, mpl::false_ /*is_sequence*/)
//         {
//             return call_synthesize(generator, sink, context, rcontext, attr, iterator);
//         }

//         // Generator has attribute (synthesize)
//         template <typename OutputIterator, typename Context, typename RContext, typename Attribute
//                   , typename Iterator>
//         static bool call(Generator const& generator
//           , OutputIterator sink, Context const& context
//           , RContext& rcontext, Attribute& attr, Iterator iterator, mpl::true_)
//         {
//             return call_synthesize_dispatch_by_seq(generator, sink, context, rcontext, attr, iterator
//                 , fusion::traits::is_sequence<Attribute>());
//         }

//         // Generator has no attribute (pass unused)
//         template <typename OutputIterator, typename Context, typename RContext, typename Attribute
//                 , typename Iterator>
//         static bool call(
//             Generator const& generator
//           , OutputIterator sink, Context const& context
//           , RContext& rcontext, Attribute& attr, Iterator iterator, mpl::false_)
//         {
//             return generator.generate(sink, context, rcontext, unused);
//         }


//     public:

//         template <typename OutputIterator, typename Context, typename RContext, typename Attribute
//                   , typename Iterator>
//         static bool call(Generator const& generator
//           , OutputIterator sink, Context const& context
//           , RContext& rcontext, Attribute& attr, Iterator iterator)
//         {
//             return call(generator, sink, context, rcontext, attr, iterator
//                        , mpl::bool_<traits::has_attribute<Generator, Context>::value>());
//         }
//     };

//     template <typename Generator, typename Context, typename RContext, typename Enable = void>
//     struct generate_from_range_impl : generate_from_range_base_impl<Generator> {};

//     template <typename Generator, typename OutputIterator, typename Context
//               , typename RContext, typename Attribute, typename Iterator>
//     bool generate_from_range(
//         Generator const& generator
//       , OutputIterator sink, Context const& context
//       , RContext& rcontext, Attribute& attr
//       , Iterator iterator)
//     {
//         return generate_from_range_impl<Generator, Context, RContext>::call(
//             generator, sink, context, rcontext, attr, iterator);
//     }

}}}}

#endif
