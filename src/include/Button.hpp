#pragma once
#include <SDL.h>
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>

#include "Texture.hpp"
#include "Globals.hpp"

//#define B_WIDTH 130*RENDERSCALE
//#define B_HEIGHT 130*RENDERSCALE

namespace GUI
{
    enum buttonType
    {
        // row 1
        CLEAR, PAREN_LEFT, PAREN_RIGHT, BACKSPACE, SLASH, 
        // row 2
        SEVEN, EIGHT, NINE, STAR,
        // row 3
        FOUR, FIVE, SIX, MINUS,
        // row 4
        ONE, TWO, THREE, PLUS,
        // row 5
        CARET, ZERO, DOT, EQUAL,
        // end
        END
    };

    // need something for the button function to return to take appropriate action
    enum action
    {
        // no action needed
        NONE,
        // indicates if expression requires rerendering
        // (any button was pressed)
        RERENDER, 
        // indicates if expression needs to be executed
        // (equal button was pressed)
        EXECUTE,
    };
     
    
    struct Button
    {
        Button(SDL_Rect dimensions, SDL_Rect clip, buttonType id, Texture* texture, action (*funct)(buttonType type, std::stringstream* stream), std::stringstream* stream);
        // returns an action if button was pressed
        action update(SDL_Event* e);
        void render();
        SDL_Rect dimensions;
        SDL_Rect clip; 
        buttonType id;
        Texture* m_texture;
        std::stringstream* m_stream;
        action (*funct)(buttonType type, std::stringstream* stream);
        int opacity;
    };
    class ButtonManager
    {
    public:
        // Very iffy code, but maybe change from static arrays to vectors?
        ButtonManager(SDL_Renderer* renderer, Texture* textures, SDL_Rect* clips, std::stringstream* stream);
        // returns true if any of the buttons were pressed
        void updateAll(SDL_Event* e);
        void renderAll();
        // void input(buttonType type);
        // sets flag to EXECUTE
        void flagExecute();
        // sets flag to RERENDER as long as flag is not set to execute
        void flagRerender();
        // sets flag to NONE
        void flagHandle();
        action flag;

    private:
        //stack allocated should be fine?
        void addButton(int x, int y, int w, int h, SDL_Rect clip, buttonType id, Texture* texture);
        void addButton(SDL_Rect dim, SDL_Rect clip, buttonType id, Texture* texture);
        std::vector<std::shared_ptr<Button>> m_buttons;
        SDL_Renderer* m_renderer;
        // pointer to the string stream and result to store math expressions
        std::stringstream* m_stream;
        // There was a way to do this algorithmically, but incase I want to
        // have more buttons that have different widths in the future
        SDL_Rect _pos[buttonType::END]; 

    };


    
} // namespace GUI
