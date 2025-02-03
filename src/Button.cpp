#include "Button.hpp"

namespace GUI
{
    Button::Button(SDL_Rect dimensions, SDL_Rect clip, buttonType id, Texture* texture, action (*funct)(buttonType type, std::stringstream* stream), std::stringstream* stream)
    : dimensions(dimensions), clip(clip), id(id), m_texture(texture), funct(funct), m_stream(stream)
    { }

    action Button::update(SDL_Event* e)
    {
        // already assume that a mouse event happened (button manager will handle that)
        int x, y;
        SDL_GetMouseState(&x, &y);

        action result;

        bool inside = true;
        if (x < dimensions.x*RENDERSCALE) inside = false;
        else if (x > dimensions.x*RENDERSCALE + dimensions.w) inside = false;
        else if (y < dimensions.y*RENDERSCALE) inside = false;
        else if (y > dimensions.y*RENDERSCALE + dimensions.h) inside = false;
        if (!inside)
        {
            opacity = 255;
        } else
        {
            switch(e->type)
            {
                case SDL_MOUSEMOTION:
                    opacity = 200;
                break;
                case SDL_MOUSEBUTTONDOWN:
                    // calls input()
                    result = funct(id, m_stream);
                    opacity = 150;
                break;
                case SDL_MOUSEBUTTONUP:
                    opacity = 200;
            }
        }
        return result;
    }

    void Button::render()
    {
        m_texture->setAlpha(opacity);
        m_texture->render(dimensions.x, dimensions.y, &clip);
    }
    
    // Note to self: If you want to add more buttons, also change the buttontype enum
    // MAKE SURE textures array size is equal to the number of buttons, otherwise error!
    ButtonManager::ButtonManager(SDL_Renderer* renderer, Texture* texture, SDL_Rect* clips, std::stringstream* stream)
        : m_renderer(renderer), m_stream(stream)
    {

        _pos[buttonType::CLEAR].x = 32;
        _pos[buttonType::CLEAR].y = 400;
        _pos[buttonType::CLEAR].w = B_WIDTH;
        _pos[buttonType::CLEAR].h = B_HEIGHT;
        
        _pos[buttonType::PAREN_LEFT].x = 194;
        _pos[buttonType::PAREN_LEFT].y = 400;
        _pos[buttonType::PAREN_LEFT].w = B_WIDTH/2;
        _pos[buttonType::PAREN_LEFT].h = B_HEIGHT;

        _pos[buttonType::PAREN_RIGHT].x = 194 + B_WIDTH;
        _pos[buttonType::PAREN_RIGHT].y = 400;
        _pos[buttonType::PAREN_RIGHT].w = B_WIDTH/2;
        _pos[buttonType::PAREN_RIGHT].h = B_HEIGHT;

        _pos[buttonType::BACKSPACE].x = 356;
        _pos[buttonType::BACKSPACE].y = 400;
        _pos[buttonType::BACKSPACE].w = B_WIDTH;
        _pos[buttonType::BACKSPACE].h = B_HEIGHT;

        _pos[buttonType::SLASH].x = 518;
        _pos[buttonType::SLASH].y = 400;
        _pos[buttonType::SLASH].w = B_WIDTH;
        _pos[buttonType::SLASH].h = B_HEIGHT;
        
        _pos[buttonType::SEVEN].x = 32;
        _pos[buttonType::SEVEN].y = 562;
        _pos[buttonType::SEVEN].w = B_WIDTH;
        _pos[buttonType::SEVEN].h = B_HEIGHT;

        _pos[buttonType::EIGHT].x = 194;
        _pos[buttonType::EIGHT].y = 562;
        _pos[buttonType::EIGHT].w = B_WIDTH;
        _pos[buttonType::EIGHT].h = B_HEIGHT;

        _pos[buttonType::NINE].x = 356;
        _pos[buttonType::NINE].y = 562;
        _pos[buttonType::NINE].w = B_WIDTH;
        _pos[buttonType::NINE].h = B_HEIGHT;

        _pos[buttonType::STAR].x = 518;
        _pos[buttonType::STAR].y = 562;
        _pos[buttonType::STAR].w = B_WIDTH;
        _pos[buttonType::STAR].h = B_HEIGHT;

        _pos[buttonType::FOUR].x = 32;
        _pos[buttonType::FOUR].y = 724;
        _pos[buttonType::FOUR].w = B_WIDTH;
        _pos[buttonType::FOUR].h = B_HEIGHT;

        _pos[buttonType::FIVE].x = 194;
        _pos[buttonType::FIVE].y = 724;
        _pos[buttonType::FIVE].w = B_WIDTH;
        _pos[buttonType::FIVE].h = B_HEIGHT;

        _pos[buttonType::SIX].x = 356;
        _pos[buttonType::SIX].y = 724;
        _pos[buttonType::SIX].w = B_WIDTH;
        _pos[buttonType::SIX].h = B_HEIGHT;

        _pos[buttonType::MINUS].x = 518;
        _pos[buttonType::MINUS].y = 724;
        _pos[buttonType::MINUS].w = B_WIDTH;
        _pos[buttonType::MINUS].h = B_HEIGHT;

        _pos[buttonType::ONE].x = 32;
        _pos[buttonType::ONE].y = 886;
        _pos[buttonType::ONE].w = B_WIDTH;
        _pos[buttonType::ONE].h = B_HEIGHT;

        _pos[buttonType::TWO].x = 194;
        _pos[buttonType::TWO].y = 886;
        _pos[buttonType::TWO].w = B_WIDTH;
        _pos[buttonType::TWO].h = B_HEIGHT;

        _pos[buttonType::THREE].x = 356;
        _pos[buttonType::THREE].y = 886;
        _pos[buttonType::THREE].w = B_WIDTH;
        _pos[buttonType::THREE].h = B_HEIGHT;

        _pos[buttonType::PLUS].x = 518;
        _pos[buttonType::PLUS].y = 886;
        _pos[buttonType::PLUS].w = B_WIDTH;
        _pos[buttonType::PLUS].h = B_HEIGHT;

        _pos[buttonType::CARET].x = 32;
        _pos[buttonType::CARET].y = 1048;
        _pos[buttonType::CARET].w = B_WIDTH;
        _pos[buttonType::CARET].h = B_HEIGHT;

        _pos[buttonType::ZERO].x = 194;
        _pos[buttonType::ZERO].y = 1048;
        _pos[buttonType::ZERO].w = B_WIDTH;
        _pos[buttonType::ZERO].h = B_HEIGHT;

        _pos[buttonType::DOT].x = 356;
        _pos[buttonType::DOT].y = 1048;
        _pos[buttonType::DOT].w = B_WIDTH;
        _pos[buttonType::DOT].h = B_HEIGHT;

        _pos[buttonType::EQUAL].x = 518;
        _pos[buttonType::EQUAL].y = 1048;
        _pos[buttonType::EQUAL].w = B_WIDTH;
        _pos[buttonType::EQUAL].h = B_HEIGHT;


        for (int i = 0; i < buttonType::END; i++)
        {
            addButton(_pos[i], clips[i], (buttonType) i, texture);
        }
    }

    action input(buttonType type, std::stringstream* stream)
    {   
        std::string newstring = stream->str();
        switch(type)
        {
            case buttonType::CLEAR:
                stream->str("");
                break;
            case buttonType::PAREN_LEFT:
                *stream << "(";
                break;
            case buttonType::PAREN_RIGHT:
                *stream << ")";
                break;
            case buttonType::BACKSPACE:
                //VERY STUPID, pipe vector of tokens directly (?)
                if (!newstring.empty())
                    newstring.pop_back();
                stream->str("");
                *stream << newstring;
                break;
            case buttonType::SLASH:
                *stream << "/";
                break;
            case buttonType::SEVEN:
                *stream << "7";
                break;
            case buttonType::EIGHT:
                *stream << "8";
                break;
            case buttonType::NINE:
                *stream << "9";
                break;
            case buttonType::STAR:
                *stream << "*";
                break;
            case buttonType::FOUR:
                *stream << "4";
                break;
            case buttonType::FIVE:
                *stream << "5";
                break;
            case buttonType::SIX:
                *stream << "6";
                break;
            case buttonType::MINUS:
                *stream << "-";
                break;
            case buttonType::ONE:
                *stream << "1";
                break;
            case buttonType::TWO:
                *stream << "2";
                break;
            case buttonType::THREE:
                *stream << "3";
                break;
            case buttonType::PLUS:
                *stream << "+";
                break;
            case buttonType::CARET:
                *stream << "^";
                break;
            case buttonType::ZERO:
                *stream << "0";
                break;
            case buttonType::DOT:
                *stream << ".";
                break;
            case buttonType::EQUAL:
                // need to figure out a way to save the results (Fix)
                return action::EXECUTE;
                
        }
        return action::RERENDER;
    }

    void ButtonManager::updateAll(SDL_Event* e)
    {
        if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
        {
            for (auto& button : m_buttons)
            {
                action nes = button->update(e);
                if (nes == action::RERENDER)
                {
                    flagRerender();
                }
                if (nes == action::EXECUTE)
                {
                    flagExecute();
                }
                
            }
        }
    }

    void ButtonManager::renderAll()
    {
        for (auto& button : m_buttons)
        {
            button->render();
        }
    }

    void ButtonManager::flagRerender()
    {
        if (flag == action::NONE)
            flag = action::RERENDER;
    }

    void ButtonManager::flagExecute()
    {
        flag = action::EXECUTE;
    }

    void ButtonManager::flagHandle()
    {
        flag = action::NONE;
    }

    void ButtonManager::addButton(int x, int y, int w, int h, SDL_Rect clip, buttonType id, Texture* texture)
    {
        SDL_Rect dim{x, y, w, h};
        m_buttons.push_back(std::move(std::make_shared<Button>(dim, clip, id, texture, &input, m_stream)));
    }
    void ButtonManager::addButton(SDL_Rect dim, SDL_Rect clip, buttonType id, Texture* texture)
    {
        m_buttons.push_back(std::move(std::make_shared<Button>(dim, clip, id, texture, &input, m_stream)));
    }
} // namespace GUI