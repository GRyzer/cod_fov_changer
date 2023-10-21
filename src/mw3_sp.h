#pragma once

#include <cinttypes>
#include <string>

#include "process.hpp"
#include "gameOptions.h"
#include "mw3.h"

namespace MW3
{
    constexpr float DefaultGravity = 800.0f;
    constexpr int DefaultSpeed = 190;
    constexpr float DefaultHighJump = 39.0f;
    constexpr float DefaultNoSpread = 0.65f;
    constexpr int DefaultEnableChaos = 0;
    constexpr float DefaultInstantAds = 1.5f;
    constexpr std::byte DefaultRapidFire = std::byte{0};

    class Singleplayer: public MW3BaseClass
    {
    public:
        Singleplayer();

        void run();

        bool set_gravity(float gravity);
        float get_gravity();

        bool set_speed(int speed);
        int get_speed();

        bool setHighJump(float highJump);
        float getHighJump();

        bool setNoSpread(float noSpread);
        float getNoSpread();

        bool enableChaos(int chaos);
        int isChaosEnabled();

        bool setInstantAds(float ads);
        float getInstantAds();

        bool setRapidFire(std::byte rapidFire);
        std::byte getRapidFire();


    private:
        const std::string _processName = "iw5sp.exe";
        Process _process;

        uint32_t _gravity_address;
        float _gravity = 20.0f;

        uint32_t _speed_address;
        int _speed = 350.0f;

        uint32_t _highJumpAddress;
        float _highJump = 170.0f;

        uint32_t _noSpreadAddress;
        float _noSpread = 0.0f;

        uint32_t _enableChaosAddress;
        int _isChaosEnabled = 1;

        uint32_t _instantAdsAddress;
        float _instantAds = DefaultInstantAds;

        uint32_t _rapidFireAddress;
        std::byte _rapidFire = std::byte{0xEB};
    };
}
