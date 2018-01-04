#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "Display.h"
//#include <Game.h>


void Display::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialised..." << std::endl;
        window = create_window(title, xpos, ypos, width, height, flags);
        if(window)
        {
            std::cout << "Window created..." << std::endl;
        }

        renderer = create_renderer(window.get(), -1, 0);
        if(renderer)
        {
            std::cout << "Renderer created..." << std::endl;
        }

        isRunning = true;
        textureAtlas = load_texture("assets/texture_atlas.png");
        if(!textureAtlas) {
            std::cout << "couldn't load img " << SDL_GetError() << std::endl;
        }

    } else {
        isRunning = false;
    }
}

std::unique_ptr<SDL_Window, sdl_deleter> Display::create_window(char const *title, int x, int y, int w, int h, Uint32 flags)
{
    return std::unique_ptr<SDL_Window, sdl_deleter>(
            SDL_CreateWindow(title, x, y, w, h, flags),
            sdl_deleter());
}
std::unique_ptr<SDL_Renderer, sdl_deleter> Display::create_renderer(SDL_Window *window, int index, Uint32 flags) {
    return std::unique_ptr<SDL_Renderer, sdl_deleter>(
            SDL_CreateRenderer(window, index, flags),
            sdl_deleter());
}

std::unique_ptr<SDL_Texture, sdl_deleter> Display::load_texture(const std::string &filename) {
    return std::unique_ptr<SDL_Texture, sdl_deleter>(
            IMG_LoadTexture_RW(renderer.get(), SDL_RWFromFile(filename.c_str(), "rb"), 1),
            sdl_deleter());
}

void Display::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    ProcessedEvent processedEvent;
    int mouse_x, mouse_y;

    switch (event.type){
        case SDL_QUIT: {
            processedEvent.exitBtn = true;
            eventQueue.push(processedEvent);
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            //std::cout << "\nX position of mouse: " << mouse_x << "\nY position of mouse: " << mouse_y << std::endl;
            processedEvent = processEvent(mouse_x, mouse_y);
            eventQueue.push(processedEvent);
        }
        default: break;
    }
}

void Display::renderBackground()
{
    SDL_Rect source, destination;
    source.h = 520;
    source.w = 780;
    source.x = 0;
    source.y = 0;

    SDL_RenderClear(renderer.get());
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), &source, NULL);
}

void Display::clean() {
    SDL_DestroyTexture(textureAtlas.get());
    SDL_DestroyRenderer(renderer.get());
    SDL_DestroyWindow(window.get());
    IMG_Quit();
    SDL_Quit();
    std::cout << "Cleaned up after Display class..." << std::endl;
}


void Display::renderField(int x, int y, bool highlighted) {
    if(highlighted) {
        SDL_Rect destination;
        destination.h = 50;
        destination.w = 50;
        destination.x = x;
        destination.y = y;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    }
}

void Display::renderPresent() {
    SDL_RenderPresent(renderer.get()); } void Display::renderField(int x, int y, bool highlighted, Color cardColor, CardType faceUpCard, int cardX, int cardY, int cardW) { if(cardW > 50) cardW = 50; SDL_Rect destination; destination.h = 50; destination.w = cardW; destination.x = cardX + (25 - cardW/2); destination.y = cardY;
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getTexturePosition(faceUpCard, cardColor), &destination);
    if(highlighted) {
        destination.x = x;
        destination.y = y;
        destination.w = 50;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    }
}

void Display::renderField(int x, int y, bool highlighted, Color cardBackColor, int cardX, int cardY, int cardW) {
    if(cardW > 50) cardW = 50;
    SDL_Rect destination;
    destination.h = 50;
    destination.w = cardW;
    destination.x = cardX + (25 - cardW/2);
    destination.y = cardY;

    if(cardBackColor == Color::BLUE) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::BLUE_CARD_BACK), &destination);
    } else {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::RED_CARD_BACK), &destination);
    }

    if(highlighted) {
        destination.x = x;
        destination.y = y;
        destination.w = 50;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    }

}

void Display::renderButton(SDL_Rect destination, UIElement texture) {
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(texture), &destination);
}

ProcessedEvent Display::getEventFromQueue() {
    ProcessedEvent result;
    if(!eventQueue.empty()) {
        result = eventQueue.front();
        eventQueue.pop();
    }
    return result;
}

bool Display::isEventQueueEmpty() {
    return eventQueue.empty();
}

ProcessedEvent Display::processEvent(int x, int y) {
    ProcessedEvent processedEvent;
    //Weed out out of bounds clicks
    if(x<10 || x>770 || y<10 || y > 510) { return processedEvent;}

    if(x>550 && x<630 && y>65 && y<95) {
        processedEvent.exitBtn = true;
    }
    if(x>660 && x<740 && y>65 && y<95) {
        processedEvent.restartBtn = true;
    }
    if(x>10 && x<510 && y>10 && y<510) {
        processedEvent.fieldIndex = processGameAreaClick(x, y);
    }
    if(x>520 && x<770 & y>110 && y<510){
        processedEvent.sideAreaIndex = processSideAreaClick(x, y);
    }
    return processedEvent;
}

int Display::processGameAreaClick(int x, int y) {
    int fieldIndex;
    fieldIndex = (((y-10)/50)*10)+((x-10)/50);
    return fieldIndex;
}

int Display::processSideAreaClick(int x, int y) {
    int sideIndex;
    sideIndex = (((y-110)/50)*5)+((x-520)/50);
    return sideIndex;
}

void Display::renderMapOverlay(Color color) {
    SDL_Rect destination;
    destination.h = 250;
    destination.w = 500;
    destination.x = 10;
    destination.y = 10;
    if(color == Color::BLUE) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MAP_OVERLAY_TOP_SHROUDED), &destination);
        destination.y = 260;
        destination.h = 50;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MAP_OVERLAY_FADE_TOP_MAP), &destination);
    } else {
        destination.y = 260;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MAP_OVERLAY_BOTTOM_SHROUDED), &destination);
        destination.y = 210;
        destination.h = 50;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MAP_OVERLAY_FADE_BOTTOM_MAP), &destination);
    }
}

void Display::renderWaitMsg(Color color) {
    SDL_Rect destination;
    destination.h = 280;
    destination.w = 250;
    destination.x = 510;
    destination.y = 110;
    if(color == Color::BLUE) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MSG_WAIT_FOR_BLUE), &destination);
    } else {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MSG_WAIT_FOR_RED), &destination);
    }
}

void Display::renderVictory(GameState victory) {
    SDL_Rect destination;
    destination.h = 150;
    destination.w = 500;
    destination.x = 10;
    destination.y = 10;

    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::VICTORY_COMMON_TOP), &destination);
    destination.y = 360;
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::VICTORY_COMMON_BOTTOM), &destination);

    destination.h = 200;
    destination.y = 160;
    if(victory == GameState::BLUE_WINS) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::VICTORY_BLUE_MID), &destination);
    } else if(victory == GameState::RED_WINS) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::VICTORY_RED_MID), &destination);
    } else if(victory == GameState::TIED) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::VICTORY_TIED), &destination);
    }

}

void Display::renderAvailableMove(int x, int y) {
    SDL_Rect destination;
    destination.h = 50;
    destination.w = 50;
    destination.x = x;
    destination.y = y;

    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::AVAILABLE_MOVE), &destination);
}

bool Display::isIsRunning() const {
    return isRunning;
}

void Display::delay() {
        SDL_Delay(0);
}

Uint32 Display::getTicks() {
    return SDL_GetTicks();
}




