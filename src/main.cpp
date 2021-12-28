#include "process.hpp"
#include "game.hpp"

#include <sstream>

#define DEFAULT_FOV 90.f
#define GITHUB "https://github.com/skudnu/cod_fov_changer"

game::GameList select_game()
{
    int game = -1;
    while (game < 0 || game > 1)
    {
        std::stringstream ss;
        ss << "[0] Modern Warfare 2\n";
        ss << "[1] Modern Warfare 3\n\n";
        ss << "Pick a Game by entering the index: ";
        std::cout << ss.str();
        std::cin >> game;
    }

    std::cout << "Index " << game << " was selected\n\n";
    return (game::GameList)game;
}

void adjust_fov_value(float* fov)
{
    while (true)
    {
        // implement functionality to change FOV value using arrow keys
        // and print new value to the console
    }
}

int main()
{
    float fov = DEFAULT_FOV;

    std::cout << "Call of Duty FOV Changer for Linux - GitHub: " << GITHUB << "\n\n";
    auto game = select_game();
    auto game_info = game::get(game);

    std::cout << "Waiting for game (" + game_info.process_name + ") to start\n";
    Process process(game_info.process_name);
    std::cout << "Game found, finding fov address\n";
    // need to sleep because we can't grab this value too early, might no be initialized yet
    std::this_thread::sleep_for(std::chrono::seconds(15));
    if (!process.find_fov_address(game_info.fov_address, game_info.fov_offset))
    {
        std::cout << "Failed to find fov address, exiting\n";
        exit(0);
    }

    std::cout << "Fov address found, starting fov changer\n";

    // std::thread input_thread(adjust_fov_value, &fov);
    // input_thread.detach();
    while (true)
    {
        if (process.get_fov() != fov)
              process.set_fov(fov);
    
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "Game exited, stopping fov changer\n";
}