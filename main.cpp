#include "Game.hpp"
Game *game = nullptr;

int main()
{
    const int FPS = 120;
    const int frameDelay = 1000/FPS;
    Uint32 framestart;
    int frameTime;

    game = new Game();
    game -> init("my game",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, false);
    while (game->running() )
    {
        framestart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - framestart;
        if(frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
    game->memclean();
    return 0;
} 