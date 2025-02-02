#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "Errors.hpp"

namespace GUI
{
    // Simple wrapper for SDL_Texture 
    class Texture
    {
    public:
        // Initalizes variables
        Texture(SDL_Renderer* renderer);

        // initializes and loads image
        Texture(SDL_Renderer* renderer, std::string path);

        // Initializes and loads font
        Texture(SDL_Renderer* renderer, TTF_Font* font);

        // Deallocate memory
        ~Texture();

        // Load image at specified path
        bool loadFromFile(std::string path);

        //Creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor = SDL_Color{0, 0, 0});

        // Deallocate texture
        void free();

        // Set Color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        // Set Alpha modulation
        void setAlpha(Uint8 alpha);

        // Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL);

        // get image dimensions
        int getWidth();
        int getHeight();
    private:
        // The actual hardware texture
        SDL_Texture* m_Texture;
        
        // Font used for rendering text
        TTF_Font* m_Font = NULL;

        // Surface pixels
        SDL_Surface* m_SurfacePixels;
        // Renderer
        SDL_Renderer* m_renderer;

        // Image dimensions
        int m_width;
        int m_height;
    };

} // namespace GUI