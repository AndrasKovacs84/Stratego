#pragma once

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <iostream>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_net.h>
#include <SDL_ttf.h>
#include "Game.h"

int main(int argc, char** argv)
{
    Game g;
    g.start();
    //_CrtDumpMemoryLeaks();
    return 0;
}