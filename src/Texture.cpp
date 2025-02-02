#include "Texture.hpp"

namespace GUI
{
    Texture::Texture(SDL_Renderer* renderer)
        : m_renderer(renderer), m_Texture(NULL), m_width(0), m_height(0)
    {}

    Texture::Texture(SDL_Renderer* renderer, std::string path)
        : Texture(renderer)
    {
            loadFromFile(path);
    }

    Texture::Texture(SDL_Renderer* renderer, TTF_Font* font)
        : Texture(renderer)
    {
        m_Font = font;
    }

    Texture::~Texture()
    {
        m_renderer = NULL;
        free();
    }

    bool Texture::loadFromFile(std::string path)
    {
        free();

        SDL_Texture* newTexture = NULL;

        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
        {
            throw Calc::RenderError("Unable to load image " + path + ", SDL_image Error: " + IMG_GetError() + "\n");
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
            if (newTexture == NULL)
            {
                throw Calc::RenderError("Unable to create texture from " + path + ", SDL Error: " + SDL_GetError() + "\n");
            }
            else
            {
                m_width = loadedSurface->w;
                m_height = loadedSurface->h;
            }

            SDL_FreeSurface(loadedSurface);
        }
        m_Texture = newTexture;
        return m_Texture != NULL;
    }

    bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
    {
        //Get rid of preexisting texture
        free();

        //Render text surface
        SDL_Surface* textSurface = TTF_RenderText_Solid( m_Font, textureText.c_str(), textColor );
        if( textSurface == NULL )
        {
            printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        else
        {
            //Create texture from surface pixels
            m_Texture = SDL_CreateTextureFromSurface( m_renderer, textSurface );
            if( m_Texture == NULL )
            {
                printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Get image dimensions
                m_width = textSurface->w;
                m_height = textSurface->h;
            }

            //Get rid of old surface
            SDL_FreeSurface( textSurface );
        }
        
        //Return success
        return m_Texture != NULL;
    }

    void Texture::free()
    {
        if (m_Texture != NULL)
        {
            // WHY is it deleting m_Texture??
            SDL_DestroyTexture(m_Texture);
            m_Texture = NULL;
            m_width = 0;
            m_height = 0;
        }
    }

    void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
    {
        SDL_SetTextureColorMod(m_Texture, red, green, blue);
    }
    void Texture::setAlpha(Uint8 alpha)
    {
        SDL_SetTextureAlphaMod(m_Texture, alpha);
    }

    void Texture::render(int x, int y, SDL_Rect* clip)
    {
        SDL_Rect renderQuad = {x, y, m_width, m_height};

        if (clip != NULL)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
        SDL_RenderCopy(m_renderer, m_Texture, clip, &renderQuad);
    }


    int Texture::getWidth()
    {
        return m_width;
    }

    int Texture::getHeight()
    {
        return m_height;
    }
} // namespace GUI

