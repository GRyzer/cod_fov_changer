#pragma once

#include <cinttypes>
#include <string>

#include "process.hpp"
#include "gameOptions.h"

namespace MW2
{
    constexpr float DefaultFov = 65.0f;
    constexpr int DefaultFPS = 60;
    
    class Multiplayer
    {
    public:
        Multiplayer();

        const uintptr_t find_address(uintptr_t fov_address, uintptr_t fov_offset);
        bool set_fov(float fov);
        float get_fov();
        bool set_fps(int fps);
        int get_fps();

        void run();

    protected:
        const std::string _processName = "iw4mp.exe";
        Process _process;

        uint32_t _fps_address;
        int _fps = 165;

        uint32_t _fov_address;
        float fov = 90.0f;
    };
}
