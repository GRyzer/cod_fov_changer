#include <iostream>
#include <string>

namespace game
{
    enum GameList
    {
        MW2,
        MW3
    };

    struct GameInfo
    {
        // general info
        std::string process_name;

        // offsets
        // how to find them:
        // https://www.unknowncheats.me/forum/call-of-duty-modern-warfare-3-a/170427-dvar-offsets-write-internal.html
        uintptr_t fov_address;
        uintptr_t fov_offset;
    };

    GameInfo get(GameList i)
    {
        GameInfo info;

        switch (i)
        {
        case MW2:
            info.process_name = "iw4mp.exe";
            info.fov_address = 0xAAC278;
            info.fov_offset = 0xC;
            break;

        case MW3:
            info.process_name = "iw5mp.exe";
            info.fov_address = 0xB0C738;
            info.fov_offset = 0xC;
            break;
        
        default:
            break;
        }

        return info;
    }
}