#pragma once
#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "TextBox.h"


struct Screenshot
{
	sf::Texture s_screenshot_textur;
	sf::Image s_screenshot;
	const sf::Uint8* pixels;
	int width;
	int height;

};

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

	void TakeScreenShot();
	
	Window m_window;
	sf::Clock m_clock;
	float m_elapsed;
	Textbox m_textbox;

	World m_world;
	Snake m_snake;
	Screenshot m_screenshot;
};