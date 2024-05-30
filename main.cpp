#include "includes/Game.h"
#include "includes/Agent.h"

#include <SFML/System/Clock.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#define PYTHON_INTERPRETER "/home/osa/anaconda3/envs/Studium/bin/python3"
#define FAST_API_URL "http://127.0.0.1:8000"

using json = nlohmann::json;

int main(int, char**) {
    // Program entry point.
    
    Game game;
    Agent agent(PYTHON_INTERPRETER, FAST_API_URL);

    game.SetAgent(&agent);
    
    sf::Clock clock;
    while (!game.GetWindow()->IsDone()) {
        //game.HandleInput();

        agent.craete_enviroment(game.GetWindow(), true);
        agent.act(game.GetSnake());
        game.Update();       
        game.Render();
        agent.calculate_reward(game.GetSnake());
        agent.craete_enviroment(game.GetWindow(), false);
        agent.update_q_value();
        game.RestartClock();

        if(agent.a_has_lost)
        {
            agent.update_exploration_rate();
            agent.restart();
        }
    }

    return 0;
}