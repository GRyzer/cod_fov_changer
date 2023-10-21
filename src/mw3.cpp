#include "mw3.h"

using namespace MW3;

MW3BaseClass::MW3BaseClass(Process& process): _fov_address(0), _process(process)
{
}

const uintptr_t MW3BaseClass::find_address(uintptr_t fov_address, uintptr_t fov_offset)
{
    uint32_t ptr = 0;
    if (!_process.read(fov_address, (void*)&ptr, sizeof(ptr)))
    {
        return 0;
    }

    return ptr + fov_offset;
}

bool MW3BaseClass::set_fov(float fov)
{
    return _process.write(_fov_address, (void*)&fov, sizeof(fov));
}

float MW3BaseClass::get_fov()
{
    float fov = MW3::DefaultFov;
    if (!_process.read(_fov_address, (void*)&fov, sizeof(fov)))
    {
        return 0.f;
    }
    
    return fov;
}

