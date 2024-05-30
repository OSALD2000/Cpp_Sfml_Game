#include "../includes/Agent.h"

Agent::Agent(std::string python_interpreter)
{
    _python_interpreter = python_interpreter;
    
    _act_json_file_name             = "env_data/act.json";
    _old_env_json_file_name         = "env_data/old_env.json";
    _action_json_file_name          = "env_data/action.json";
    _new_env_json_file_name         = "env_data/new_env.json";

    _old_head_pos_json_file_name    = "env_data/old_head_pos.json";
    _new_head_pos_json_file_name    = "env_data/new_head_pos.json";
    _old_apple_pos_json_file_name   = "env_data/old_apple_pos.json";
    _new_apple_pos_json_file_name   = "env_data/new_apple_pos.json";

    _act_python_file_name = "/home/osa/Private/C_Sfml_Game/build/agent/act.py";
    _update_q_value_python_file_name = "/home/osa/Private/C_Sfml_Game/build/agent/update_q_values.py";

    _reward_json_file_name = "env_data/reward.json";

    _env.new_pixel_map = nullptr;
    _env.old_pixel_map = nullptr;

    _env.old_apple_pos[0] = -1;
    _env.old_apple_pos[1] = -1;

    _env.new_apple_pos[0] = -1;
    _env.new_apple_pos[1] = -1;

    _env.old_head_pos[0] = -1;
    _env.old_head_pos[1] = -1;

    _env.new_head_pos[0] = -1;
    _env.new_head_pos[1] = -1;

    _env.reward = 0;
    _env.old_scoure = 0;

    _exploration_rate = 1;
    _max_exploration_rate = 1;
    _min_exploration_rate = 0.01;
    _exploration_decay_rate = 0.01;

    a_has_lost = false;
}

Agent::~Agent()
{
}

void Agent::craete_enviroment(Window* window, bool before_act)
{
    _env.image_texture.create(window->GetRenderWindow()->getSize().x, window->GetRenderWindow()->getSize().y);
    _env.image_texture.update(*window->GetRenderWindow());
    sf::Image screenshot = _env.image_texture.copyToImage();
    if(before_act)
    {
        if (_env.new_pixel_map != nullptr)
        {
            delete _env.old_pixel_map;
            _env.old_pixel_map = _env.new_pixel_map;
            _env.new_pixel_map = nullptr;
        }
        else
        {
            _env.old_pixel_map = get_features(screenshot, before_act);
            _env.new_pixel_map = nullptr;
        }
        json env_old(*_env.old_pixel_map);
        json old_head_pos = {_env.old_head_pos[0], _env.old_head_pos[1]};
        json old_apple_pos = {_env.old_apple_pos[0], _env.old_apple_pos[1]};

        write_in_file(_old_env_json_file_name       , env_old);
        write_in_file(_old_head_pos_json_file_name  , old_head_pos);
        write_in_file(_old_apple_pos_json_file_name , old_apple_pos);
        
    }
    else
    {
        _env.new_pixel_map = get_features(screenshot, before_act);
        json env_new(*_env.old_pixel_map);
        json new_head_pos = {_env.new_head_pos[0], _env.new_head_pos[1]};
        json new_apple_pos = {_env.new_apple_pos[0], _env.new_apple_pos[1]};
        
        write_in_file(_new_env_json_file_name, env_new);
        write_in_file(_new_head_pos_json_file_name  , new_head_pos);
        write_in_file(_new_apple_pos_json_file_name , new_apple_pos);
    }
}

void Agent::act(Snake* m_snake)
{
    int action;
    srand(time(0));
    _env.old_scoure = m_snake->GetScore();

    double exploration_threshold  = static_cast<double>(rand())/ RAND_MAX;
    if(exploration_threshold > _exploration_rate)
    {
        std::system((_python_interpreter + " " + _act_python_file_name).c_str());
        action = get_action();
    }
    else
    {
        action = rand() % 4;
    }

        
    if (action == Action::UP
        && m_snake->GetPhysicalDirection() != Direction::Down)
    {
        m_snake->SetDirection(Direction::Up);
    }
    else if ( action == Action::DOWN
        && m_snake->GetPhysicalDirection() != Direction::Up)
    {
        m_snake->SetDirection(Direction::Down);
    }
    else if (action == Action::LEFT
        && m_snake->GetPhysicalDirection() != Direction::Right)
    {
        m_snake->SetDirection(Direction::Left);
    }
    else if (action == Action::RIGHT
        && m_snake->GetPhysicalDirection() != Direction::Left)
    {
        m_snake->SetDirection(Direction::Right);
    }

}

void Agent::update_q_value()
{       
    json reward;
    reward["reward"] = _env.reward;

    write_in_file(_reward_json_file_name, reward);

    std::system((_python_interpreter + " " + _update_q_value_python_file_name).c_str());
}

void Agent::update_exploration_rate()
{
    _exploration_rate = _min_exploration_rate + 
                        (_max_exploration_rate - _min_exploration_rate) * std::exp(-_exploration_decay_rate);
}

void Agent::write_in_file(std::string file_name, json& data)
{
    std::ofstream file(file_name);
    if (file.is_open()) {
        file << std::setw(1) << data << std::endl;
        file.close();
    } 
}


std::vector<std::vector<int>>* Agent::get_features(sf::Image& screenshot, bool before_act)
{
        unsigned int width  = screenshot.getSize().x;
        unsigned int height = screenshot.getSize().y;

        unsigned int red_sum   = 0;
        unsigned int blue_sum  = 0;
        unsigned int green_sum = 0;

        unsigned int red_mean   = 0;
        unsigned int blue_mean  = 0;
        unsigned int green_mean = 0;

        std::vector<int> row;
        std::vector<std::vector<int>>* map = new std::vector<std::vector<int>>;;
        
        for (unsigned int y = 0; y <= height-20; y+=20)
        {
            std::vector<int> row;

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
                    row.push_back(WORLD_CREATIORS::SNAKE_HEAD_CELL);
                    if(before_act)
                    {
                        _env.old_head_pos[0] = x / 20;
                        _env.old_head_pos[1] = y / 20;
                    }
                    else
                    {
                        _env.new_head_pos[0] = x / 20;
                        _env.new_head_pos[1] = y / 20;
                    }
                }
                else if (red_mean > 100)
                {
                    row.push_back(WORLD_CREATIORS::FOOD_CELL);

                    if(before_act)
                    {
                        _env.old_apple_pos[0] = x / 20;
                        _env.old_apple_pos[1] = y / 20;
                    }
                    else
                    {
                        _env.new_apple_pos[0] = x / 20;
                        _env.new_apple_pos[1] = y / 20;
                    }
                }
                else if (blue_mean > 100)
                {
                    row.push_back(WORLD_CREATIORS::WALL_CELL);
                }
                else if (green_mean > 100)
                {
                    row.push_back(WORLD_CREATIORS::SNAKE_CELL);
                }
                else 
                {
                    row.push_back(WORLD_CREATIORS::EMPTY_CELL);
                }
        }

        map->push_back(row);
    }

    return map;

};


json Agent::read_from_file(std::string file_name)
{
    std::ifstream file(file_name);
    json data;
    if (file.is_open()) {
        file >> data;
        file.close();
    }
    return data;
}

int Agent::get_action()
{
   json data = read_from_file(_action_json_file_name);
   std::string action = data["action"];
   int action_int = std::stoi(action);

   return action_int;
}


void Agent::calculate_reward(Snake* m_snake)
{
    if (a_has_lost)
    {
        _env.reward += REWARD::DEATH_REWARD;
    }
    else if (m_snake->GetScore() > _env.old_scoure)
    {
        _env.reward += REWARD::FOOD_REWARD;
    }
    else
    {
        _env.reward += REWARD::MOVE_REWARD;
    }
}

void Agent::restart()
{
    if(_env.old_pixel_map != nullptr)
    {
        delete _env.old_pixel_map;
        _env.old_pixel_map = nullptr;
    }
    if(_env.new_pixel_map != nullptr)
    {
        delete _env.new_pixel_map;
        _env.new_pixel_map = nullptr;
    }

    _env.old_apple_pos[0] = -1;
    _env.old_apple_pos[1] = -1;

    _env.new_apple_pos[0] = -1;
    _env.new_apple_pos[1] = -1;

    _env.old_head_pos[0] = -1;
    _env.old_head_pos[1] = -1;

    _env.new_head_pos[0] = -1;
    _env.new_head_pos[1] = -1;

    _env.reward = 0;
    _env.old_scoure = 0;

    a_has_lost = false;
}