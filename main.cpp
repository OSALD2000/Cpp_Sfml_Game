#include "includes/Game.h"
#include "includes/Agent.h"

#include <SFML/System/Clock.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#define PYTHON_INTERPRETER "/home/osa/anaconda3/envs/Studium/bin/python3"

using json = nlohmann::json;

int main(int, char**) {
    // Program entry point.
    
    Game game;
    Agent agent(PYTHON_INTERPRETER);

    
    sf::Clock clock;
    while (!game.GetWindow()->IsDone()) {
        game.HandleInput();
        game.Update();
        game.Render();
        
        agent.craete_enviroment(game.GetWindow(), true);
        agent.act();
        
        // craete fueature to update q value
        // update q value
        // check if game is over
        // if game is over, update exploration_rate
        
        game.RestartClock();
    }

    return 0;
}






    // std::vector<std::vector<int>> c_vector {
    //     std::vector<int> {1, 2, 3, 4},
    //     std::vector<int> {1, 2, 3, 4},
    //     std::vector<int> {1, 2, 3, 4},
    // };

    // json j_vec(c_vector);

    // std::ofstream o("env_data/test.json");
    // o << std::setw(4) << j_vec << std::endl;