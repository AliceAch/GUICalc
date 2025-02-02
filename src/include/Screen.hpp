#pragma once
#include <sstream>
#include <Texture.hpp>

#include "Globals.hpp"

namespace GUI
{
    class Screen
    {
    public:
        Screen(SDL_Renderer* renderer, Texture* ExpressionTexture, Texture* ResultTexture, std::stringstream* expression, std::string* result);
        void update();
        void render();
        void showResult(bool value);

    private:
        SDL_Renderer* m_Renderer;
        Texture* m_ExpressionTexture;
        Texture* m_ResultTexture;
        std::stringstream* m_expression;
        std::string* m_result;
        bool m_showResult = false;
        bool empty = false;
    };    
} // namespace GUI
