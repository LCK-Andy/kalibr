#ifndef PORTABLE_BINARY_ARCHIVE_HPP
#define PORTABLE_BINARY_ARCHIVE_HPP

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

// breaking changes in boost >=1.59
#if BOOST_VERSION >= 105900
#else
#include <boost/serialization/pfto.hpp>
#endif

#include <boost/static_assert.hpp>

#include <climits>
#if CHAR_BIT != 8
#error This code assumes an eight-bit byte.
#endif

#include <boost/archive/basic_archive.hpp>

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

namespace boost
{
    namespace archive
    {
        enum portable_binary_archive_flags
        {
            endian_big = 0x4000,
            endian_little = 0x8000
        };

        // #if ( endian_big <= boost::archive::flags_last )
        // #error archive flags conflict
        // #endif

        inline void
        reverse_bytes(char size, char *address)
        {
            char *first = address;
            char *last = first + size - 1;
            for (; first < last; ++first, --last)
            {
                char x = *last;
                *last = *first;
                *first = x;
            }
        }

    } // namespace archive
} // namespace boost

#endif // PORTABLE_BINARY_ARCHIVE_HPP
