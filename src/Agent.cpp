#include "../includes/Agent.h"

Agent::Agent(string python_interpreter)
{
    _python_interpreter = python_interpreter;
    
    _act_json_file_name = "act.json";
    _old_env_json_file_name = "old_env.json";
    _action_json_file_name = "action.json";
    _new_env_json_file_name = "new_env.json";

    _act_python_file_name = "agent/act.py";
    _update_q_value_python_file_name = "agent/update_q_value.py";
}

Agent::~Agent()
{
}

void Agent::craete_enviroment(Window* window, bool before_act)
{
    sf::Image screenshot = window->GetWindow().capture();
    
    if(before_act)
    {
        _env.old_pixel_map = screenshot.getPixelsPtr();
        _env.new_pixel_map = NULL
    }
    else
    {
        _env.new_pixel_map = image.getPixelsPtr();
    }

    
}

void Agent::act()
{
    // do something
}

void Agent::update_q_value()
{
    // do something
}

void Agent::check_game_over()
{
    // do something
}

void Agent::update_exploration_rate()
{
    // do something
}

void Agent::write_in_file(string file_name)
{
    // Open the file for writing
    std::ofstream file(file_name);

    // Check if the file was successfully opened
    if (file.is_open()) {
        // Write data to the file
        file << "Hello, world!";

        // Close the file
        file.close();
    } else {
        // Print an error message if the file could not be opened
        cout << "Error opening file: " << file_name << endl;
    }
}


std::vector<std::vector<int>>* Agent::get_features(sf::Image& screenshot)
{
        unsigned int width  = screenshot.getSize().x;
        unsigned int height = screenshot.getSize().y;

        unsigned int red_sum   = 0;
        unsigned int blue_sum  = 0;
        unsigned int green_sum = 0;

        unsigned int red_mean   = 0;
        unsigned int blue_mean  = 0;
        unsigned int green_mean = 0;

                
        for (unsigned int y = 0; y <= height-20; y+=20)
        {
            for (unsigned int x = 0; x <= width-20; x+=20)
            {
                red_sum = 0;
                blue_sum = 0;
                green_sum = 0;

                for (unsigned int i = 0; i < 10; i++)
                {
                    sf::Color pixelColor = screenshot.getPixel(x+i, y+i);
                    red_sum += pixelColor.r;
                    blue_sum += pixelColor.b;
                    green_sum += pixelColor.g;
                }

                red_mean = red_sum / 10;
                blue_mean = blue_sum / 10;
                green_mean = green_sum / 10;

                if (red_mean > 100 && green_mean > 100)
                {
                    _features.push_back(1);
                }
                else if (red_mean > 100)
                {
                    _features.push_back(1);
                }
                else if (blue_mean > 100)
                {
                    _features.push_back(1);
                }
                else if (green_mean > 100)
                {
                    _features.push_back(1);
                }
                else 
                {
                    _features.push_back(0);
                }
                
        }
};