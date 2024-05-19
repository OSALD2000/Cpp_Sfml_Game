#include "../../includes/04_chapter/Window.h"
#include "../../includes/04_chapter/Game.h"

void Game::MoveSprite(EventDetails* l_details){
        sf::Vector2i mousepos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
        m_mushroom.setPosition(mousepos.x, mousepos.y);
        std::cout << "Moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
}


Game::Game() :m_window("Chapter 2", sf::Vector2u(800, 600))
{
    // Setting up class members.
    m_mushroomTexture.loadFromFile("./resources/Mushroom.png");
    m_mushroom.setTexture(m_mushroomTexture);
    m_increment = sf::Vector2i(400, 400); // 400px a second.
    m_frametime = 1.0f / 60.0f;


    std::string eventName = "Move";
    m_window.GetEventManager()->AddCallback(eventName, &Game::MoveSprite, this);
};

Game::~Game()
{
};

void Game::HandleInput()
{
};

void Game::Update()
{
    if (m_elapsed.asSeconds() >= m_frametime)
    {
        m_window.Update(); // Update window events.
        m_elapsed -= sf::seconds(m_frametime);
    }
};


Window* Game::GetWindow()
{
    return &m_window;
};


void Game::MoveMushroom()
{
    float fElapsed = m_elapsed.asSeconds();

    sf::Vector2u l_windSize = m_window.GetWindowSize();
    sf::Vector2u l_textSize = m_mushroomTexture.getSize();

    if ((m_mushroom.getPosition().x >
        l_windSize.x - l_textSize.x && m_increment.x > 0) ||
        (m_mushroom.getPosition().x < 0 && m_increment.x < 0)) {
        m_increment.x = -m_increment.x;
    }

    if ((m_mushroom.getPosition().y >
        l_windSize.y - l_textSize.y && m_increment.y > 0) ||
        (m_mushroom.getPosition().y < 0 && m_increment.y < 0)) {
        m_increment.y = -m_increment.y;
    }

    m_mushroom.setPosition(
        m_mushroom.getPosition().x + (m_increment.x * fElapsed),
        m_mushroom.getPosition().y + (m_increment.y * fElapsed));
};

void Game::Render()
{
    m_window.BeginDraw(); // Clear.
    m_window.Draw(m_mushroom);
    m_window.EndDraw(); // Display.
};

sf::Time Game::GetElapsed()
{
    return m_elapsed;
};

void Game::RestartClock()
{
    m_elapsed += m_clock.restart();
};