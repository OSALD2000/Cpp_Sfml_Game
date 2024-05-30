#include "../includes/Agent.h"

Agent::Agent(std::string python_interpreter, std::string api_url)
{
    _python_interpreter = python_interpreter;
    _api_url = api_url;

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

    _curl = curl_easy_init();
    if (!_curl)
    {
        std::cerr << "Curl failed to initialize" << std::endl;
        throw std::runtime_error("Curl failed to initialize");
    }
}


Agent::~Agent()
{
        if (_curl) {
            curl_easy_cleanup(_curl);
        }
}


size_t write_action_callback(void *contents, size_t size, size_t nmemb, std::string *buffer)
 {
    size_t total_size = size * nmemb;
    buffer->append(static_cast<char*>(contents), total_size);
    return total_size;
 }
 


void Agent::craete_enviroment(Window* window, bool before_act)
{
    _env.image_texture.create(window->GetRenderWindow()->getSize().x, window->GetRenderWindow()->getSize().y);
    _env.image_texture.update(*window->GetRenderWindow());
    sf::Image screenshot = _env.image_texture.copyToImage();

    _curl = curl_easy_init();
    if (!_curl)
    {
            std::cerr << "Curl failed to initialize" << std::endl;
            throw std::runtime_error("Curl failed to initialize");
    }

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
        
        json data = {
            {"old_map", *_env.old_pixel_map},
            {"head_pos", {_env.old_head_pos[0], _env.old_head_pos[1]}},
            {"apple_pos", {_env.old_apple_pos[0], _env.old_apple_pos[1]}}
        };


        std::string json_data = data.dump();

        
        curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, json_data.c_str());

        struct curl_slist* headers = NULL;

        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(_curl, CURLOPT_URL, (_api_url+"/env_before_act").c_str());
        curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(_curl);

        if (res != CURLE_OK)
        {
            throw std::runtime_error("Curl failed to perform");
        }
    }
    else
    {
        _env.new_pixel_map = get_features(screenshot, before_act);

        json data = {
            {"old_map", *_env.new_pixel_map},
            {"head_pos", {_env.new_head_pos[0], _env.new_head_pos[1]}},
            {"apple_pos", {_env.new_apple_pos[0], _env.new_apple_pos[1]}}
        };

                std::string json_data = data.dump();
 
        curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, json_data.c_str());

        struct curl_slist* headers = NULL;

        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(_curl, CURLOPT_URL, (_api_url+"/env_after_act").c_str());
        curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(_curl);

        if (res != CURLE_OK)
        {
            throw std::runtime_error("Curl failed to perform");
        }
    }

    curl_easy_cleanup(_curl);
}

void Agent::act(Snake* m_snake)
{
    int action;
    srand(time(0));
    _env.old_scoure = m_snake->GetScore();

    double exploration_threshold  = static_cast<double>(rand())/ RAND_MAX;

    if(exploration_threshold > _exploration_rate)
    {
        action = rand() % 4;
    }
    else
    {
        action = get_action();
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
}

void Agent::update_exploration_rate()
{
    _exploration_rate = _min_exploration_rate + 
                        (_max_exploration_rate - _min_exploration_rate) * std::exp(-_exploration_decay_rate);
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



int Agent::get_action()
{
    _curl = curl_easy_init();
    if (!_curl)
    {
        std::cerr << "Curl failed to initialize" << std::endl;
        throw std::runtime_error("Curl failed to initialize");
    }

    std::string action_buffer;

    struct curl_slist* headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(_curl, CURLOPT_URL, (_api_url+"/action").c_str());
    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(_curl, CURLOPT_HTTPGET, 1L);

    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_action_callback);

    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &action_buffer);

    CURLcode res = curl_easy_perform(_curl);

    json response_json = json::parse(action_buffer);

    std::string action = response_json["action"];

    int action_int = std::stoi(action);

    curl_easy_cleanup(_curl);
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

