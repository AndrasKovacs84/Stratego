#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "Display.h"
//#include <Game.h>


void Display::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialised..." << std::endl;
        window = create_window(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created..." << std::endl;
        }

        renderer = create_renderer(window.get(), -1, 0);
        if (renderer)
        {
            std::cout << "Renderer created..." << std::endl;
        }

        isRunning = true;
        textureAtlas = load_texture("assets/texture_atlas.png");
        if (!textureAtlas) {
            std::cout << "couldn't load img " << SDL_GetError() << std::endl;
        }

        if (TTF_Init() == -1) {
            printf("TTF_Init: %s\n", TTF_GetError());
            exit(2);
        }
        menuFont = load_font("assets/Sketch_Gothic_School.ttf");
        if (!menuFont)
        {
            std::cout << "couldn't load font " << TTF_GetError() << std::endl;
        }

    }
    else {
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

std::unique_ptr<TTF_Font, sdl_deleter> Display::load_font(const std::string & filename)
{
    return std::unique_ptr<TTF_Font, sdl_deleter>(
        TTF_OpenFont(filename.c_str(), 42),
        sdl_deleter());
}

std::unique_ptr<SDL_Texture, sdl_deleter> Display::text_to_texture(TTF_Font* font, const std::string & text, SDL_Color color)
{
    SDL_Surface* surfaceMsg = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* textureMsg = SDL_CreateTextureFromSurface(renderer.get(), surfaceMsg);
    SDL_FreeSurface(surfaceMsg);
    return std::unique_ptr<SDL_Texture, sdl_deleter>(textureMsg);
}

void Display::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    ProcessedEvent processedEvent;
    int mouse_x, mouse_y;

    switch (event.type) {
    case SDL_QUIT: {
        processedEvent.exitBtn = true;
        eventQueue.push(processedEvent);
        break;
    }
    case SDL_MOUSEBUTTONDOWN: {
        SDL_GetMouseState(&mouse_x, &mouse_y);
        processedEvent = InputParser::getInstance()->processEvent(mouse_x, mouse_y, InputType::MOUSE_CLICK_DOWN);
        eventQueue.push(processedEvent);
        mouseBtnDown = 1;
        break;
    }
    case SDL_MOUSEBUTTONUP: {
        if (mouseBtnDown)
        {
            SDL_GetMouseState(&mouse_x, &mouse_y);
            processedEvent = InputParser::getInstance()->processEvent(mouse_x, mouse_y, InputType::MOUSE_CLICK_RELEASE);
            eventQueue.push(processedEvent);
        }
        mouseBtnDown = 0;
        break;
    } 
    case SDL_KEYDOWN: {
        processedEvent = InputParser::getInstance()->processKeyEvent(event);
        eventQueue.push(processedEvent);
    }
    default: break;
    }
}

void Display::renderBackground()
{
    SDL_Rect source;
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
    if (highlighted) {
        SDL_Rect destination;
        destination.h = 50;
        destination.w = 50;
        destination.x = x;
        destination.y = y;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    }
}

void Display::renderPresent() {
    SDL_RenderPresent(renderer.get());
} void Display::renderField(int x, int y, bool highlighted, Color cardColor, CardType faceUpCard, int cardX, int cardY, int cardW) {
    if (cardW > 50) cardW = 50; SDL_Rect destination; destination.h = 50; destination.w = cardW; destination.x = cardX + (25 - cardW / 2); destination.y = cardY;
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getTexturePosition(faceUpCard, cardColor), &destination);
    if (highlighted) {
        destination.x = x;
        destination.y = y;
        destination.w = 50;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::FIELD_HIGHLIGHT), &destination);
    }
}

void Display::renderField(int x, int y, bool highlighted, Color cardBackColor, int cardX, int cardY, int cardW) {
    if (cardW > 50) cardW = 50;
    SDL_Rect destination;
    destination.h = 50;
    destination.w = cardW;
    destination.x = cardX + (25 - cardW / 2);
    destination.y = cardY;

    if (cardBackColor == Color::BLUE) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::BLUE_CARD_BACK), &destination);
    }
    else {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::RED_CARD_BACK), &destination);
    }

    if (highlighted) {
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
    if (!eventQueue.empty()) {
        result = eventQueue.front();
        eventQueue.pop();
    }
    return result;
}

bool Display::isEventQueueEmpty() {
    return eventQueue.empty();
}

void Display::renderSubmenu(Submenu & submenu)
{
    SDL_Rect destination;
    int x = submenu.getNextX();
    int y = 0;
    destination.h = 510;
    destination.w = 500;
    destination.x = x;
    destination.y = 0;
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MENU), &destination);

    size_t menuSize = submenu.getMenuSize();
    std::string btnCaption;
    SDL_Color white = { 255, 255, 255 };
    for (size_t i = 0; i < menuSize; i++)
    {
        btnCaption = submenu.getCaption(i);
        if (btnCaption != "")
        {
            std::unique_ptr<SDL_Texture, sdl_deleter> caption = text_to_texture(menuFont.get(), btnCaption, white);
            x = submenu.getBtnX();
            y = submenu.getBtnY(i);
            destination.x = x;
            destination.y = y;
            destination.w = 270;
            destination.h = 50;
            if (submenu.isBtnPressed(i))
            {
                SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MENU_BTN_PRESSED), &destination);
            }
            else
            {
                SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MENU_BTN), &destination);
            }
            
            int btnWidth = destination.w;
            int btnHeight = destination.h;
            SDL_QueryTexture(caption.get(), NULL, NULL, &destination.w, &destination.h);
            destination.x = x + (btnWidth - destination.w) / 2;
            destination.y = y + (btnHeight - destination.h) / 2;
            if (submenu.isBtnPressed(i))
            {
                destination.y += 2; // Render the caption 2 px below normal to make the btn look pressed in
            }
            SDL_RenderCopy(renderer.get(), caption.get(), NULL, &destination);
        }
    }
}

void Display::renderMapOverlay(Color color) {
    SDL_Rect destination;
    destination.h = 250;
    destination.w = 500;
    destination.x = 10;
    destination.y = 10;
    if (color == Color::BLUE) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MAP_OVERLAY_TOP_SHROUDED), &destination);
        destination.y = 260;
        destination.h = 50;
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MAP_OVERLAY_FADE_TOP_MAP), &destination);
    }
    else {
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
    if (color == Color::BLUE) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MSG_WAIT_FOR_BLUE), &destination);
    }
    else {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MSG_WAIT_FOR_RED), &destination);
    }
}

void Display::renderVictory(Color playerColor) {
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
    if (playerColor == Color::BLUE) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::VICTORY_BLUE_MID), &destination);
    }
    else if (playerColor == Color::RED) {
        SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::VICTORY_RED_MID), &destination);
    }
}

void Display::renderVictory()
{
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
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::VICTORY_TIED), &destination);
}

void Display::renderAvailableMove(int x, int y) {
    SDL_Rect destination;
    destination.h = 50;
    destination.w = 50;
    destination.x = x;
    destination.y = y;

    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::AVAILABLE_MOVE), &destination);
}

void Display::renderMenu(const std::unique_ptr<MainMenu>& menu)
{
    size_t x = 0;
    size_t y = 0;
    SDL_Rect destination;
    destination.h = 260;
    destination.w = 780;
    destination.x = 0;
    y = menu->getNextY(true);
    destination.y = y;
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MENU_BACK_TOP), &destination);
    destination.x = 0;
    y = menu->getNextY(false);
    destination.y = y;
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::MENU_BACK_BOTTOM), &destination);

    SubmenuName currentSubmenuName = States::getInstance()->getCurrentSubmenu();
    SubmenuName previousSubmenuName = States::getInstance()->getPreviousSubmenu();
    if (previousSubmenuName != SubmenuName::NONE)
    {
        Submenu& previousSubmenu = menu->getSubmenu(previousSubmenuName);
        if (previousSubmenu.isAnimated())
        {
            renderSubmenu(previousSubmenu);
        }
    }
    if (currentSubmenuName != SubmenuName::NONE)
    {
        Submenu& currentSubmenu = menu->getSubmenu(currentSubmenuName);
        renderSubmenu(currentSubmenu);
    }

}

void Display::renderSplash()
{
    SDL_RenderCopy(renderer.get(), textureAtlas.get(), assets.getUIElement(UIElement::SPLASH), NULL);
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




