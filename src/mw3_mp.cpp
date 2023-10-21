#include <iostream>
#include <sstream>
#include <map>

#include "gameOptions.h"
#include "mw3_mp.h"

using namespace MW3;

Multiplayer::Multiplayer(): _process(_processName), MW3BaseClass(_process)
{
    GameOption gameOption = getMultiPlayerOption(MultiplayerOption::FOV);
    _fov_address = find_address(gameOption.address, gameOption.offset);

    gameOption = getMultiPlayerOption(MultiplayerOption::FPS);
    _fps_address = find_address(gameOption.address, gameOption.offset);

    gameOption = getMultiPlayerOption(MultiplayerOption::FOG);
    _fog_address = find_address(gameOption.address, gameOption.offset);

    set_fps(_fps); 
}

void Multiplayer::run()
{
    while (_process.is_running())
    {
        if (get_fov() != fov)
            set_fov(fov);
        if (get_fps() != _fps)
            set_fps(_fps);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

bool Multiplayer::set_fps(int fps)
{
    return _process.write(_fps_address, (void*)&fps, sizeof(fps));
}

int Multiplayer::get_fps()
{
    int fps = DefaultFPS;
    if (!_process.read(_fps_address, (void*)&fps, sizeof(fps)))
    {
        return 0;
    }
    
    return fps;
}

bool Multiplayer::set_fog(int fog)
{
    return _process.write(_fog_address, (void*)&fog, sizeof(fog));
}

int Multiplayer::get_fog()
{
    int fog = DefaultFOG;
    if (!_process.read(_fog_address, (void*)&fog, sizeof(fog)))
    {
        return 0;
    }
    
    return fog;
}

int main(int argc, char const *argv[])
{
    auto game = MW3::Multiplayer();
    game.run();
    return 0;
}
