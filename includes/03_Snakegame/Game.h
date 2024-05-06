#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"

class Game{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	float GetElapsed();
	void RestartClock();

	Window* GetWindow();
private:
	Window m_window;
	sf::Clock m_clock;
	float m_elapsed;

	World m_world;
	Snake m_snake;
};