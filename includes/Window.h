#pragma once
#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();
	void Destroy();

	bool IsDone();
	bool IsFullscreen();
	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();

	void Draw(sf::Drawable& l_drawable);

	sf::RenderWindow m_window;
	bool m_isDone;

private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Create();

	
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isFullscreen;
};