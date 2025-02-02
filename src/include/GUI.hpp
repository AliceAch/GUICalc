#pragma once
#include <list>
#include "Texture.hpp"
#include "Button.hpp"
#include "Screen.hpp"

namespace GUI
{
    
    class Calc_GUIManager
    {
    public:
        Calc_GUIManager(std::stringstream* expression, std::string* result);
        bool checkFlagEXECUTE();
        // set a flag in Screen that is reset when a button is pressed 
        void showcase();
        void hide();
        // initializes SDL and other necessary libraries
        bool init();
        // load all of the necessary textures/fonts
        bool load();
        // renders body, screen, and button
        void render();
        // checks if rerender is necessary and renders the screen if it is
        void rerender();
        // updates screen and buttons
        void update(SDL_Event* e);
        // frees all the resources and closes SDL / other libraries
        void close();

    private:
        SDL_Rect screen_rect;
        std::stringstream* m_expression;
        std::string* m_result;
        bool m_ShowResult;        
        SDL_Window* m_window = NULL;
        SDL_Renderer* m_renderer = NULL;
        SDL_Rect m_SpriteClips[21];
        Texture* m_ButtonTexture;
        Texture* m_ScreenText;
        Texture* m_ResultText;
        TTF_Font* m_Font;
        // heap allocated because cannot guarantee SDL initialized properly
        ButtonManager* m_ButtonManager;
        Screen* m_Screen;
    };

} // namespace GUI