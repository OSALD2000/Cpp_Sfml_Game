#include "includes/Game.h"
#include <SFML/System/Clock.hpp>

int main(int, char**) {
    // Program entry point.
    Game game;
    sf::Clock clock;
    while (!game.GetWindow()->IsDone()) {
        game.HandleInput();
        game.Update();
        game.Render();
        
        // craete fueature to act 
        // agent act
        // craete fueature to update q value
        // update q value
        // check if game is over
        // if game is over, update exploration_rate
        
        game.RestartClock();

        // Limit the frame rate to reduce CPU usage
        sf::Time elapsed = clock.restart();
        sf::Time frameTime = sf::seconds(1.0f / 60.0f);
        if (elapsed < frameTime) {
            sf::sleep(frameTime - elapsed);
        }
    }

    return 0;
}