#include "mw2.h"

using namespace MW2;

Multiplayer::Multiplayer(): _process(_processName)
{
    GameOption gameOption = getMultiPlayerOption(MultiplayerOption::FOV);
    _fov_address = find_address(gameOption.address, gameOption.offset);

    gameOption = getMultiPlayerOption(MultiplayerOption::FPS);
    _fps_address = find_address(gameOption.address, gameOption.offset);
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

const uintptr_t Multiplayer::find_address(uintptr_t fov_address, uintptr_t fov_offset)
{
    uint32_t ptr = 0;
    if (!_process.read(fov_address, (void*)&ptr, sizeof(ptr)))
    {
        return 0;
    }

    return ptr + fov_offset;
}

bool Multiplayer::set_fov(float fov)
{
    return _process.write(_fov_address, (void*)&fov, sizeof(fov));
}

float Multiplayer::get_fov()
{
    float fov = MW2::DefaultFov;
    if (!_process.read(_fov_address, (void*)&fov, sizeof(fov)))
    {
        return 0.f;
    }
    
    return fov;
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

int main(int argc, char const *argv[])
{
    auto game = MW2::Multiplayer();
    game.run();
    return 0;
}