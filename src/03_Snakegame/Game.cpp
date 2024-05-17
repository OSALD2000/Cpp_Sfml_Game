#include "../../includes/03_Snakegame/Game.h"

Game::Game() :m_window("Chapter 2", sf::Vector2u(800, 600)),
m_world(sf::Vector2u(800, 600)), m_snake(m_world.GetBlockSize())
{
    m_textbox.Setup(5,14,350,sf::Vector2f(225,0));
    m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
};

Game::~Game()
{
};

void Game::HandleInput()
{  
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        && m_snake.GetPhysicalDirection() != Direction::Down)
    {
        m_snake.SetDirection(Direction::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
        && m_snake.GetPhysicalDirection() != Direction::Up)
    {
        m_snake.SetDirection(Direction::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
        && m_snake.GetPhysicalDirection() != Direction::Right)
    {
        m_snake.SetDirection(Direction::Left);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
        && m_snake.GetPhysicalDirection() != Direction::Left)
    {
        m_snake.SetDirection(Direction::Right);
    }
};

void Game::Update()
{
    float timestep = 1.0f / m_snake.GetSpeed();

    if (m_elapsed >= timestep) {
        m_snake.Tick();
        m_world.Update(m_snake);
        m_window.Update();
        m_elapsed -= timestep;
        TakeScreenShot();
        if (m_snake.HasLost()) {
            m_snake.Reset();
        }
    }
};


Window* Game::GetWindow()
{
    return &m_window;
};


void Game::Render()
{
    m_window.BeginDraw();
    // Render here.
    m_world.Render(*m_window.GetRenderWindow());
    m_snake.Render(*m_window.GetRenderWindow());

    m_window.EndDraw();
};

float Game::GetElapsed()
{
    return m_elapsed;
};

void Game::RestartClock()
{

    m_elapsed += m_clock.restart().asSeconds();

};

void Game::TakeScreenShot()
{
   sf::Vector2u windowSize = m_window.GetRenderWindow()->getSize();
   m_screenshot.s_screenshot_textur.create(windowSize.x, windowSize.y);
   m_screenshot.s_screenshot_textur.update(*m_window.GetRenderWindow());
   m_screenshot.s_screenshot = m_screenshot.s_screenshot_textur.copyToImage();
   m_screenshot.s_screenshot.saveToFile("screenshot.png");

   return;
}