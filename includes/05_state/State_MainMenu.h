#pragma once

#include "StateManager.h"

class State_MainMenu : public BaseState{
public:
    State_MainMenu(StateManager* l_shared) : BaseState(l_shared){};
    ~State_MainMenu(){};
    
    void OnCreate() override;
    void OnDestroy() override;
    void Activate() override;
    void Deactivate() override;
    void Update(const sf::Time& l_time) override;
    void Draw() override;
    
    void MouseClick(EventDetails* l_details);
private:
    sf::Text m_text;
    sf::Font m_font;
    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    unsigned int m_buttonPadding;

    sf::RectangleShape m_rects[3];
    sf::Text m_labels[3];
};