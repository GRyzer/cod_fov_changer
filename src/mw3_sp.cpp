#include <iostream>
#include <sstream>
#include <map>

#include "gameOptions.h"
#include "mw3_sp.h"

using namespace MW3;

Singleplayer::Singleplayer(): _process(_processName), _gravity_address(0), MW3BaseClass(_process)
{
    GameOption gameOption = getSinglePlayerOption(SingleplayerOption::FOV);
    _fov_address = find_address(gameOption.address, gameOption.offset);

    gameOption = getSinglePlayerOption(SingleplayerOption::Gravity);
    _gravity_address = find_address(gameOption.address, gameOption.offset);

    gameOption = getSinglePlayerOption(SingleplayerOption::Speed);
    _speed_address = find_address(gameOption.address, gameOption.offset);

    gameOption = getSinglePlayerOption(SingleplayerOption::HighJump);
    _highJumpAddress = find_address(gameOption.address, gameOption.offset);

    gameOption = getSinglePlayerOption(SingleplayerOption::NoSpread);
    _noSpreadAddress = find_address(gameOption.address, gameOption.offset);

    gameOption = getSinglePlayerOption(SingleplayerOption::EnableChaos);
    _enableChaosAddress = find_address(gameOption.address, gameOption.offset);

    gameOption = getSinglePlayerOption(SingleplayerOption::InstantAds);
    _instantAdsAddress = find_address(gameOption.address, gameOption.offset);

    gameOption = getSinglePlayerOption(SingleplayerOption::RapidFire);
    _rapidFireAddress = find_address(gameOption.address, gameOption.offset);
}

void Singleplayer::run()
{
    while (_process.is_running())
    {
        if (get_fov() != fov)
            set_fov(fov);
        //if (get_gravity() != _gravity)
        //    set_gravity(_gravity);
        if(get_speed() != _speed)
            set_speed(_speed);
        if(getHighJump() != _highJump)
            setHighJump(_highJump);
        /*if(getInstantAds() != _instantAds)
            setInstantAds(_instantAds);  */  
        //const auto test = getRapidFire();
        //std::cout << "getRapidFire: " << getRapidFire() << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

bool Singleplayer::set_gravity(float gravity)
{
    return _process.write(_gravity_address, (void*)&gravity, sizeof(gravity));
}

float Singleplayer::get_gravity()
{
    float gravity = DefaultGravity;
    if (!_process.read(_gravity_address, (void*)&gravity, sizeof(gravity)))
    {
        return 0.f;
    }
    
    return gravity;
}

bool Singleplayer::set_speed(int speed)
{
    return _process.write(_speed_address, (void*)&speed, sizeof(speed));
}

int Singleplayer::get_speed()
{
    int speed = DefaultSpeed;
    if(!_process.read(_speed_address, (void*)&speed, sizeof(speed)))
    {
        return 0;
    }

    return speed;
}

bool Singleplayer::setHighJump(float highJump)
{
    return _process.write(_highJumpAddress, (void*)&highJump, sizeof(highJump));
}

float Singleplayer::getHighJump()
{
    float highJump = DefaultHighJump;
    if(!_process.read(_highJumpAddress, (void*)&highJump, sizeof(highJump)))
    {
        return 0.0f;
    }

    return highJump;
}

bool Singleplayer::setNoSpread(float noSpread)
{
    return _process.write(_noSpreadAddress, (void*)&noSpread, sizeof(noSpread));
}

float Singleplayer::getNoSpread()
{
    float noSpread = DefaultNoSpread;
    if(!_process.read(_noSpreadAddress, (void*)&noSpread, sizeof(noSpread)))
    {
        return 0.0f;
    }

    return noSpread;
}

bool Singleplayer::enableChaos(int chaos)
{
    return _process.write(_enableChaosAddress, (void*)&chaos, sizeof(chaos));
}

int Singleplayer::isChaosEnabled()
{
    int chaos = DefaultEnableChaos;
    if(!_process.read(_enableChaosAddress, (void*)&chaos, sizeof(chaos)))
    {
        return 0;
    }

    return chaos;
}

bool Singleplayer::setInstantAds(float instantAds)
{
    return _process.write(_instantAdsAddress, (void*)&instantAds, sizeof(instantAds));
}

float Singleplayer::getInstantAds()
{
    float instantAds = DefaultInstantAds;
    if(!_process.read(_instantAdsAddress, (void*)&instantAds, sizeof(instantAds)))
    {
        return 0.0f;
    }

    return instantAds;
}

bool Singleplayer::setRapidFire(std::byte rapidFire)
{
    return _process.write(_rapidFireAddress, (void*)&rapidFire, sizeof(rapidFire));
}

std::byte Singleplayer::getRapidFire()
{
    std::byte rapidFire = std::byte{0};
    if(!_process.read(_rapidFireAddress, (void*)&rapidFire, sizeof(rapidFire)))
    {
        return std::byte{0};
    }

    return std::byte{0};
}

int main(int argc, char const *argv[])
{
    auto game = MW3::Singleplayer();
    game.run();
    return 0;
}
