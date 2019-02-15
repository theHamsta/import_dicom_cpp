#ifndef Q_MOC_RUN
#    undef Q_FOREACH
#    undef foreach
#    include <openvdb/openvdb.h>
#    pragma pop_macro("Q_FOREACH")
#    pragma pop_macro("foreach")
#endif

#include <openvdb/tools/Dense.h>

#include "ImageToNumpy.hpp"

template< class T >
using Grid_T = openvdb::Grid< typename openvdb::tree::Tree4< T, 5, 4, 3 >::Type >;
template< class T >
using GridPtr_T = typename Grid_T< T >::Ptr;

template< class T >
GridPtr_T< T > numpyToOpenVdb(pybind11::array_t< T > array, float clippingTolerance = 0.f)
{
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
                    if (r(k, j, i) != 0.f) { accessor.setValue(ijk, r(k, j, i)); }
    }
    else
    {
        throw std::runtime_error("Array is not a volume!");
    }

    grid->pruneGrid(clippingTolerance);
    return grid;
}
