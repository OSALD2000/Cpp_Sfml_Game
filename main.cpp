#include "includes/Game.h"
#include "includes/Agent.h"

#include <SFML/System/Clock.hpp>
#include <fstream>
#include <vector>

#define PYTHON_INTERPRETER "/home/osa/anaconda3/envs/Studium/bin/python3"
#define FAST_API_URL "http://127.0.0.1:8000"


int main(int, char**) {
    // Program entry point.
    
    Game game;
    Agent agent(PYTHON_INTERPRETER, FAST_API_URL);

    game.SetAgent(&agent);
    
    sf::Clock clock;
    while (!game.GetWindow()->IsDone()){
        //int action = game.HandleInput();
        //game.Render();
        //agent.craete_enviroment(game.GetWindow(), true);
        //agent.act(game.GetSnake());
        game.Update();       
        game.Render();
        // agent.craete_enviroment(game.GetWindow(), action);
        // agent.calculate_reward(game.GetSnake());
        // agent.save_data();

        // agent.update_q_value();
        game.RestartClock();
        if(agent.a_has_lost)
        {
            //agent.update_exploration_rate();
            agent.restart();
        }
    }

    agent.save_buffer();
}