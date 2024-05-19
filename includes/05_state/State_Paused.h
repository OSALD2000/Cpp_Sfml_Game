#pragma once

#include "StateManager.h"


class State_Paused : public BaseState{
public:
    
    State_Paused(StateManager* l_shared) : BaseState(l_shared){};
    ~State_Paused(){};

    void OnCreate() override;
    void OnDestroy() override;
    void Activate() override;
    void Deactivate() override;
    void Update(const sf::Time& l_time) override;
    void Draw() override;
    
    void Unpause(EventDetails* l_details);
private:
    sf::Text m_text;
    sf::Font m_font;
    sf::RectangleShape m_rect;
};