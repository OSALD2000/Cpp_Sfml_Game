#include "includes/03_Snakegame/Game.h"

int main(int, char**) {
    // Program entry point.
    Game game; // Creating our game object.
    while (!game.GetWindow()->IsDone()) {
        // Game loop.
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }

    return 0;
}