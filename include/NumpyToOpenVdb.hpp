#pragma once
#ifndef Q_MOC_RUN
#    pragma push_macro("Q_FOREACH")
#    pragma push_macro("foreach")
#    undef Q_FOREACH
#    undef foreach
#    include <openvdb/openvdb.h>
#    include <openvdb/tools/Dense.h>
#    pragma pop_macro("Q_FOREACH")
#    pragma pop_macro("foreach")
#endif

#include "ImageToNumpy.hpp"

template< class T >
using Grid_T = openvdb::Grid< typename openvdb::tree::Tree4< T, 5, 4, 3 >::Type >;
template< class T >
using GridPtr_T = typename Grid_T< T >::Ptr;

template< class T >
GridPtr_T< T > numpyToOpenVdb(const pybind11::array_t< T >& array, T absoluteTolerance = static_cast< T >(0),
                              float pruningTolerance = 0.f)
{
	openvdb::initialize();
    GridPtr_T< T > grid = Grid_T< T >::create();
    auto accessor       = grid->getAccessor();
    openvdb::Coord ijk;

    int &i = ijk[0], &j = ijk[1], &k = ijk[2];

    if (array.ndim() == 3)
    {
        auto r = array.template unchecked< 3 >();

        for (k = 0; k < r.shape(0); k++)
            for (j = 0; j < r.shape(1); j++)
                for (i = 0; i < r.shape(2); i++)
                    if (std::abs(r(k, j, i)) > absoluteTolerance) { accessor.setValue(ijk, r(k, j, i)); }
    }
    else
    {
        throw std::runtime_error("Array is not a volume!");
    }

    grid->pruneGrid(pruningTolerance);
    return grid;
}

template< class T >
GridPtr_T< T > imageToOpenVdb(const std::string& filename, T absoluteTolerance = static_cast< T >(0),
                              float pruningTolerance = 0.f)
{
    auto array = imageToNumpy< T >(filename);
    auto grid  = numpyToOpenVdb< T >(array, absoluteTolerance, pruningTolerance);
    return grid;
}
