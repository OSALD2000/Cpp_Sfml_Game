#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "TextBox.h"
#include "Agent.h"


class Game{
public:
	Game();
	~Game();

	int HandleInput();
	void Update();
	void Render();

	float GetElapsed();
	void RestartClock();

	Window* GetWindow();

	Snake* GetSnake();

	void SetAgent(Agent* agent);

	
private:

	Window m_window;
	sf::Clock m_clock;
	float m_elapsed;
	Textbox m_textbox;

	World 	m_world;
	Snake 	m_snake;
	Agent* 	m_agent;
	int m_action;
};