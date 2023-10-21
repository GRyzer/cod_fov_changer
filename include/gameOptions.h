#pragma once

#include <cinttypes>

struct GameOption
{
    uintptr_t address;
    uintptr_t offset;
};

namespace MW2
{
    enum class MultiplayerOption
    {
        FOV,
        FPS
    };


    inline GameOption getMultiPlayerOption(MultiplayerOption option)
    {
        GameOption gameOption{};

        switch(option)
        {
            case MultiplayerOption::FOV:
                gameOption.address = 0xAAC1F8;
                gameOption.offset = 0xC;
                break;

            case MultiplayerOption::FPS:
                gameOption.address = 0x1B90730; //https://github.com/PierroD/Market/blob/main/LINDRA%20-%20Market/MarketOffsets/Offsets/iw4mp.cs
                gameOption.offset = 0xC;
                break;
        }

        return gameOption;
    }
}

namespace MW3
{
    enum class SingleplayerOption
    {
        FOV,
        Gravity,
        Speed,
        HighJump,
        NoSpread,
        EnableChaos,
        InstantAds,
        RapidFire
    };

    enum class MultiplayerOption
    {
        FOV,
        FPS,
        FOG
    };

    inline GameOption getSinglePlayerOption(SingleplayerOption option)
    {
        GameOption gameOption{};

        switch(option)
        {
            case SingleplayerOption::FOV:
                gameOption.address = 0xA76130;
                gameOption.offset = 0xC;
                break;

            case SingleplayerOption::Gravity:
                gameOption.address = 0x1D36EEC; //dword_1D36EEC = sub_4F9CC0((int)"g_gravity", 800.0, 1.0, 3.4028235e38, 192);
                gameOption.offset = 0xC;
                break;
            
            case SingleplayerOption::Speed:
                gameOption.address = 0x1357A80;
                gameOption.offset = 0xC;
                break;
            
            case SingleplayerOption::HighJump:
                gameOption.address = 0x1d35a90;
                gameOption.offset = 0xC;
                break;
            
            case SingleplayerOption::NoSpread: // Probably not working
                gameOption.address = 0x1d398a8;
                gameOption.offset = 0xC;
                break;
            
            case SingleplayerOption::EnableChaos: //Not Working
                gameOption.address = 0x1f1570c;
                gameOption.offset = 0xC;
                break; 

            case SingleplayerOption::InstantAds: // Don't know if it works
                gameOption.address = 0x1D398AC;
                gameOption.offset = 0xC;
                break;     

            case SingleplayerOption::RapidFire: //Not Working
                //gameOption.address = 0x246bf6;
                gameOption.address = 0x4a2420;
                gameOption.offset = 0x0;
                break;                             
        }

        return gameOption;
    }

    inline GameOption getMultiPlayerOption(MultiplayerOption option)
    {
        GameOption gameOption{};

        switch(option)
        {
            case MultiplayerOption::FOV:
                gameOption.address = 0xB0C738;
                gameOption.offset = 0xC;
                break;

            case MultiplayerOption::FPS:
                gameOption.address = 0x1CF0B84; //https://github.com/ZeroMemes/BetterCOD/blob/master/bettercod/codadapter.cpp
                gameOption.offset = 0xC;
                break;

            case MultiplayerOption::FOG:
                gameOption.address = 0x5FC091C;
                gameOption.offset = 0xC;
                break;
        }

        return gameOption;
    }
}
