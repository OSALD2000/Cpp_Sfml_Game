#pragma once
#include "Window.h"
#include <string>
#include <vector>
#include <fstream> 
#include <nlohmann/json.hpp>


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


class Agent
{
public:
    Agent(std::string python_interpreter);
    ~Agent();
    void craete_enviroment(Window* window, bool before_act);
    void act();
    void update_q_value();
    void check_game_over();
    void update_exploration_rate();
    
private:
    void write_in_file(std::string file_name, json& data);
    std::vector<std::vector<int>>* get_features(sf::Image& image, bool before_act);
    Environment _env;
    std::string _python_interpreter;
    std::string _act_json_file_name;
    std::string _action_json_file_name;
    std::string _old_env_json_file_name;
    std::string _new_env_json_file_name;
    std::string _old_head_pos_json_file_name;
    std::string _new_head_pos_json_file_name;
    std::string _old_apple_pos_json_file_name;
    std::string _new_apple_pos_json_file_name;
    std::string _act_python_file_name;
    std::string _update_q_value_python_file_name;
};
