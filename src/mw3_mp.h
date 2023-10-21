#pragma once

#include <cinttypes>
#include <string>

#include "process.hpp"
#include "gameOptions.h"
#include "mw3.h"

namespace MW3
{
    constexpr int DefaultFPS = 60;
    constexpr int DefaultFOG = 0;

    class Multiplayer: public MW3BaseClass
    {
    public:
        Multiplayer();

        void run();
        bool set_fps(int fps);
        int get_fps();

        bool set_fog(int fog);
        int get_fog();

    private:
        const std::string _processName = "iw5mp.exe";
        Process _process;

        uint32_t _fps_address;
        int _fps = 165;

        uint32_t _fog_address;
        int _fog = 0;
    };
}
