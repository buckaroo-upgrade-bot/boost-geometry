// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_ROTATION_QUATERNION_CONCEPT_HPP
#define BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_ROTATION_QUATERNION_CONCEPT_HPP

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry { namespace concepts {

template <typename Geometry>
class RotationQuaternion
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename coordinate_type<Geometry>::type ctype;
    typedef typename coordinate_system<Geometry>::type csystem;

    template <typename G, std::size_t I, std::size_t N>
    struct dimension_checker
    {
        static void apply()
        {
            G* g = 0;
            geometry::set<I>(*g, geometry::get<I>(*g));
            dimension_checker<G, I+1, N>::apply();
        }
    };


    template <typename G, std::size_t N>
    struct dimension_checker<G, N, N>
    {
        static void apply() {}
    };

public:

    /// BCCL macro to apply the Vector concept
    BOOST_CONCEPT_USAGE(RotationQuaternion)
    {
        static const bool dim_check = dimension<Geometry>::value == 3;
        BOOST_MPL_ASSERT_MSG(dim_check, INVALID_DIMENSION, (RotationQuaternion));
        static const bool cs_check = ::boost::is_same<csystem, cs::cartesian>::value;
        BOOST_MPL_ASSERT_MSG(cs_check, NOT_IMPLEMENTED_FOR_THIS_CS, (csystem));

        dimension_checker<Geometry, 0, 4>::apply();
    }
#endif
};


template <typename Geometry>
class ConstRotationQuaternion
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename coordinate_type<Geometry>::type ctype;
    typedef typename coordinate_system<Geometry>::type csystem;

    template <typename G, std::size_t I, std::size_t N>
    struct dimension_checker
    {
        static void apply()
        {
            const G* g = 0;
            ctype coord(geometry::get<I>(*g));
            boost::ignore_unused(coord);
            dimension_checker<G, I+1, N>::apply();
        }
    };


    template <typename G, std::size_t N>
    struct dimension_checker<G, N, N>
    {
        static void apply() {}
    };

public:

    /// BCCL macro to apply the ConstVector concept
    BOOST_CONCEPT_USAGE(ConstRotationQuaternion)
    {
        static const bool dim_check = dimension<Geometry>::value == 3;
        BOOST_MPL_ASSERT_MSG(dim_check, INVALID_DIMENSION, (ConstRotationQuaternion));
        static const bool cs_check = ::boost::is_same<csystem, cs::cartesian>::value;
        BOOST_MPL_ASSERT_MSG(cs_check, NOT_IMPLEMENTED_FOR_THIS_CS, (csystem));

        dimension_checker<Geometry, 0, 4>::apply();
    }
#endif
};

}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_ROTATION_QUATERNION_CONCEPT_HPP
