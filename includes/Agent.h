#pragma once
#include "Window.h"
#include "Snake.h"
#include <string>
#include <vector>
#include <fstream> 
#include <nlohmann/json.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <curl/curl.h>


using json = nlohmann::json;

struct Environment
{
    sf::Texture image_texture;
    std::vector<std::vector<int>>* old_pixel_map;
    std::vector<std::vector<int>>* new_pixel_map;
    int old_head_pos[2];
    int new_head_pos[2];
    int old_apple_pos[2];
    int new_apple_pos[2];
    int action;
    int reward;
    int old_state;
    int next_state;
    bool done;
    int old_scoure;
};

enum Action
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

//enum State{};

enum WORLD_CREATIORS
{
    EMPTY_CELL = 0,
    WALL_CELL  = 1,
    FOOD_CELL  = 2,
    SNAKE_CELL = 3,
    SNAKE_HEAD_CELL = 4    
};

enum REWARD
{
    FOOD_REWARD = 1000,
    DEATH_REWARD = -2000,
    MOVE_REWARD = -1
};

enum STATE
{
    SNAKE_RUNING = 0,
    SNAKE_DEAD = 1,
    SNAKE_EATING = 2, 
};


class Agent
{
public:
    Agent(std::string python_interpreter, std::string api_url);
    ~Agent();
    void craete_enviroment(Window* window, bool before_act);
    void act(Snake* m_snake);
    void calculate_reward(Snake* m_snake);
    void update_q_value();
    void update_exploration_rate();
    void restart();

    bool a_has_lost;
    
private:
    int  get_action();

    std::vector<std::vector<int>>* get_features(sf::Image& image, bool before_act);
    Environment     _env;
    std::string     _python_interpreter;
    std::string _api_url;
    CURL*          _curl;


    float  _exploration_rate;
    float  _exploration_decay_rate;
    float  _min_exploration_rate;
    float  _max_exploration_rate;
};
