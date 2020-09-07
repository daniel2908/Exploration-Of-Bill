#include "Game.hpp"
#include <iostream>
#include "tilemap.hpp"
#include "textures.hpp"
#include "GameObj.hpp"
#include "ecs.hpp"
#include "Components.hpp"
using namespace std;

GameObject* player;
GameObject* enemy;
Map* map;
SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());



Game::Game()
{

}
Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{   
    int flags=0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "initialized :)" << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            cout << "window opened!" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "render opened" << endl;
        }
        isrunning = true;
    } 
        else 
        {
            isrunning = false;
        }
    player = new GameObject("wiz.png", 0 ,0 );
    enemy = new GameObject("skelly.png", 50, 50);
    map = new Map();
    newPlayer.addComponent<PositionComponent>(); 
    
}
void Game::handleEvents()
{
 SDL_Event event;
 SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
        isrunning = false;
        break;
        default:
        break;
    }

}

void Game::update()
{
    player->update();
    enemy->update();
    manager.update();
    std::cout << newPlayer.getComponent<PositionComponent>().x() << endl;
    
    
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    player->Render();
    enemy->Render();
    SDL_RenderPresent(renderer);

}

void Game::memclean()
{
SDL_DestroyWindow(window);
SDL_DestroyRenderer(renderer);
SDL_Quit();
cout << "goodbye" << endl;
}