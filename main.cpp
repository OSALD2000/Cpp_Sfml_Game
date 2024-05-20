#include "includes/Game.h"

int main(int, char**) {
    // Program entry point.
    Game game;
    while(!game.GetWindow()->IsDone()){
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }
}