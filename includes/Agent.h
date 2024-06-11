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

// struct Environment
// {
//     sf::Texture image_texture;
//     std::vector<std::vector<int>>* old_pixel_map;
//     std::vector<std::vector<int>>* new_pixel_map;
//     int old_head_pos[2];
//     int new_head_pos[2];
//     int old_apple_pos[2];
//     int new_apple_pos[2];
//     int action;
//     int reward;
//     int old_state;
//     int next_state;
//     bool done;
//     int old_scoure;
// };

struct Body
{
    int x;
    int y;
    friend void to_json(json& j, const Body& b) {
        j = json{{b.x, b.y}};
    }
    friend void from_json(const json& j, Body& b) {
        j.at("position")[0].get_to(b.x);
        j.at("position")[1].get_to(b.y);
    }
};


struct Environment
{
    int head_pos[2];
    int apple_pos[2];
    std::vector<Body> snake_body;
    int action;
    int reward;
    int old_state;
    int next_state;
    bool done;
    int old_scoure;

    friend void to_json(json& j, const Environment& b) {
        j = json{
            {"head_pos", {b.head_pos[0], b.head_pos[1]}},
            {"apple_pos", {b.apple_pos[0], b.apple_pos[1]}},
            {"snake_body", b.snake_body},
            {"action", b.action},
            {"reward", b.reward},
        };
    }

    friend void from_json(const json& j, Environment& b) {
    
    }
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
    void craete_enviroment(Window* window, int action);
    void act(Snake* m_snake);
    void calculate_reward(Snake* m_snake);
    void update_q_value();
    void update_exploration_rate();
    void restart();
    void save_data();
    void save_buffer();
    bool a_has_lost;
    
private:
    int  get_action();

    // std::vector<std::vector<int>>* get_features(sf::Image& image, bool before_act);
    std::vector<Body> get_features(sf::Image& image);
    Environment     _env;
    std::string     _python_interpreter;
    std::string _api_url;
    CURL*          _curl;


    sf::Texture _image_texture;
    float  _exploration_rate;
    float  _exploration_decay_rate;
    float  _min_exploration_rate;
    float  _max_exploration_rate;

    std::vector<Environment>* _replay_buffer;
};
