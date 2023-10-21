#pragma once

#include <cinttypes>
#include <string>

#include "process.hpp"
#include "gameOptions.h"

namespace MW3
{
    constexpr float DefaultFov = 65.0f;
    
    class MW3BaseClass
    {
    public:
        MW3BaseClass(Process& process);

        const uintptr_t find_address(uintptr_t fov_address, uintptr_t fov_offset);
        bool set_fov(float fov);
        float get_fov();

    protected:
        Process& _process;

        uint32_t _fov_address;
        float fov = 90.0f;
    };
}
