#pragma once
#include "StateManager.h"

class State_Intro : public BaseState{
public:
    State_Intro(StateManager* l_shared) : BaseState(l_shared){};
    ~State_Intro(){};

    void OnCreate() override;
    void OnDestroy() override;
    void Activate() override;
    void Deactivate() override;
    void Update(const sf::Time& l_time) override;
    void Draw() override;
    
    void Continue(EventDetails* l_details);

private:
    sf::Texture m_introTexture;
    sf::Sprite m_introSprite;
    sf::Text m_text;
    sf::Font m_font;
    float m_timePassed;
};