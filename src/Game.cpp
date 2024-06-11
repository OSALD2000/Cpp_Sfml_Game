#include "../includes/Game.h"

Game::Game() :m_window("SNAKE_GAME_WINDOWS", sf::Vector2u(800, 800)),
m_world(sf::Vector2u(800, 800)), m_snake(m_world.GetBlockSize())
{
    m_textbox.Setup(5,14,350,sf::Vector2f(225,0));
    m_textbox.Add("Seeded random number generator with: " + std::to_string(time(NULL)));
};

Game::~Game()
{
};

int Game::HandleInput()
{  
    
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
    //     && m_snake.GetPhysicalDirection() != Direction::Down)
    // {
    //     m_snake.SetDirection(Direction::Up);
    // }
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
    //     && m_snake.GetPhysicalDirection() != Direction::Up)
    // {
    //     m_snake.SetDirection(Direction::Down);
    // }
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
    //     && m_snake.GetPhysicalDirection() != Direction::Right)
    // {
    //     m_snake.SetDirection(Direction::Left);
    // }
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    //     && m_snake.GetPhysicalDirection() != Direction::Left)
    // {
    //     m_snake.SetDirection(Direction::Right);
    // }

    int action;

    sf::Event event;

    while (m_window.m_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            m_window.Destroy();
            m_window.m_isDone = true;    
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Up
                && m_snake.GetPhysicalDirection() != Direction::Down)
            {
                m_action = 0;
                m_snake.SetDirection(Direction::Up);
            }
            else if (event.key.code == sf::Keyboard::Down
                && m_snake.GetPhysicalDirection() != Direction::Up)
            {
                m_action = 1;
                m_snake.SetDirection(Direction::Down);
            }
            else if (event.key.code == sf::Keyboard::Left
                && m_snake.GetPhysicalDirection() != Direction::Right)
            {
                m_action = 2;
                m_snake.SetDirection(Direction::Left);
            }
            else if (event.key.code == sf::Keyboard::Right
                && m_snake.GetPhysicalDirection() != Direction::Left)
            {
                m_action = 3;
                m_snake.SetDirection(Direction::Right);
            }
            break;
        }
    }
    return m_action;
}

void Game::Update()
{
    float timestep = 1.0f / m_snake.GetSpeed();

    if (m_elapsed >= timestep) {
        m_agent->craete_enviroment(GetWindow(), m_action);
        m_agent->act(m_snake);
        m_snake.Tick();
        m_world.Update(m_snake);
        m_window.Update();
        m_agent->calculate_reward(GetSnake());
        m_agent->save_data();
        m_elapsed -= timestep;
        if (m_snake.HasLost()) {
            m_snake.Reset();
            m_agent->a_has_lost = true;
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

Snake* Game::GetSnake()
{
    return &m_snake;
};


void Game::SetAgent(Agent* agent)
{
    m_agent = agent;
};