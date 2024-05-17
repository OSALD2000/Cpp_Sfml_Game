#include "includes/04_chapter/Game.h"

int main(int, char**) {
    // Program entry point.
    Game game; // Creating our game object.
    while (!game.GetWindow()->IsDone()) {
        // Game loop.
        game.Update();
        game.Render();
        game.RestartClock();
    }

    return 0;
}
