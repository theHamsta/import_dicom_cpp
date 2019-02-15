#include <iostream>

#include "ImageToNumpy.hpp"
#include "NumpyToOpenVdb.hpp"

int main()
{
    auto interpreter     = std::make_unique< pybind11::scoped_interpreter >();
    std::string filename = "/media/dos/MRT_A/NEURORAD_MS_ED_WISSENSCHAFT_20180723_152155_000000/"
                           "CS_TOF_SV_0P31ISO_ACC8_SEG3_0013/MRT_A_ORIGINAL_PRIMARY_M_ND_100_93.IMA";

    auto volume  = imageToNumpy<float>(filename);
    auto volume3 = imageToNumpy<int>(filename);
    std::cout << volume.at(3, 4, 20) << std::endl;

    auto grid = numpyToOpenVdb(volume3);
    std::cout << "Grid has " << grid->activeVoxelCount() << " voxels." << std::endl;
    auto foo  = imageToOpenVdb<int>(filename, 400);
    std::cout << "Grid has " << foo->activeVoxelCount() << " voxels." << std::endl;
}
