#ifndef Game_H
#define Game_H


#include "Window.h"

class Game{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();

private:
    void MoveMushroom();
    Window m_window;
    sf::Texture m_mushroomTexture;
    sf::Sprite  m_mushroom;
    sf::Vector2f m_increment;
};

#endif