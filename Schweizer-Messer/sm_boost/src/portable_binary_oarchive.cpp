/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// portable_binary_oarchive.cpp

// (C) Copyright 2002-7 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>

// Use boost::detail::endian if available, otherwise use standard detection
#ifdef BOOST_VERSION
#if BOOST_VERSION < 107000
#include <boost/detail/endian.hpp>
#else
// For Boost >= 1.70, use standard C++17 endianness detection or fallback
#include <climits>
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define BOOST_LITTLE_ENDIAN
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BOOST_BIG_ENDIAN
#endif
#elif defined(_WIN32) || defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == 1234)
#define BOOST_LITTLE_ENDIAN
#elif defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == 4321)
#define BOOST_BIG_ENDIAN
#else
#define BOOST_LITTLE_ENDIAN // Default fallback
#endif
#endif
#endif

#include <boost/portable_binary_oarchive.hpp>

namespace boost
{
    namespace archive
    {

        void
        portable_binary_oarchive::save_impl(
            const boost::intmax_t l,
            const char /* maxsize */
        )
        {
            char size = 0;

            if (l == 0)
            {
                this->primitive_base_t::save(size);
                return;
            }

            boost::intmax_t ll;
            bool negative = (l < 0);
            if (negative)
                ll = -l;
            else
                ll = l;

            do
            {
                ll >>= CHAR_BIT;
                ++size;
            } while (ll != 0);

            this->primitive_base_t::save(
                static_cast<char>(negative ? -size : size));

            if (negative)
                ll = -l;
            else
                ll = l;
            char *cptr = reinterpret_cast<char *>(&ll);
#ifdef BOOST_BIG_ENDIAN
            cptr += (sizeof(boost::intmax_t) - size);
            if (m_flags & endian_little)
                reverse_bytes(size, cptr);
#else
            if (m_flags & endian_big)
                reverse_bytes(size, cptr);
#endif
            this->primitive_base_t::save_binary(cptr, size);
        }

        void
        portable_binary_oarchive::init(unsigned int flags)
        {
            if (m_flags == (endian_big | endian_little))
            {
                boost::serialization::throw_exception(
                    portable_binary_oarchive_exception());
            }
            if (0 == (flags & boost::archive::no_header))
            {
                // write signature in an archive version independent manner
                const std::string file_signature(
                    boost::archive::BOOST_ARCHIVE_SIGNATURE());
                *this << file_signature;
                // write library version
                const boost::archive::library_version_type v(
                    boost::archive::BOOST_ARCHIVE_VERSION());
                *this << v;
            }
            save(static_cast<unsigned char>(m_flags >> CHAR_BIT));
        }

    } // namespace archive
} // namespace boost
#include <boost/archive/impl/archive_serializer_map.ipp>
#include <boost/archive/impl/basic_binary_oprimitive.ipp>

namespace boost
{
    namespace archive
    {

        namespace detail
        {
            template class archive_serializer_map<portable_binary_oarchive>;
        }

        template class basic_binary_oprimitive<
            portable_binary_oarchive,
            std::ostream::char_type,
            std::ostream::traits_type>;

    } // namespace archive
} // namespace boost
