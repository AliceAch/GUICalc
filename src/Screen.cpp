#include "Screen.hpp"

namespace GUI
{
    Screen::Screen(SDL_Renderer* renderer, Texture* ExpressionTexture, Texture* ResultTexture, std::stringstream* expression, std::string* result)
    : m_Renderer(renderer), m_ExpressionTexture(ExpressionTexture), m_ResultTexture(ResultTexture), m_expression(expression), m_result(result)
    {
    }
    void Screen::update()
    {
        if(!m_expression->str().empty())
        {
           empty = false;
            m_ExpressionTexture->loadFromRenderedText(m_expression->str(), SDL_Color{255, 255, 255});
        }
        else
        {
            empty = true;
        }
        if(m_showResult)
        {
            m_ResultTexture->loadFromRenderedText(*m_result, SDL_Color{255, 255, 255});
        }
        
    }
    void Screen::render()
    {
        if(!empty)
        {
            m_ExpressionTexture->render(0, 0);
            
        }
        if(m_showResult)
        {
            m_ResultTexture->loadFromRenderedText(*m_result, SDL_Color{255, 255, 255});
            // Adjust right (Fix)
            m_ResultTexture->render(0, m_ResultTexture->getHeight()*RENDERSCALE+30);
        }

    }

    void Screen::showResult(bool value)
    {
        m_showResult = value;
    }
} // namespace GUI