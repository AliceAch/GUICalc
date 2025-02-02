#include "GUI.hpp"

namespace GUI
{        
    Calc_GUIManager::Calc_GUIManager(std::stringstream* expression, std::string* result)
    : m_expression(expression), m_result(result)
    { 
        screen_rect = {0, 0, SCREEN_WIDTH*2, 358};
    }

    bool Calc_GUIManager::checkFlagEXECUTE()
    {
        return m_ButtonManager->flag == action::EXECUTE;
    }

    void Calc_GUIManager::showcase()
    {
        m_ShowResult = true;
        m_Screen->showResult(true);
    }

    void Calc_GUIManager::hide()
    {
        if(m_ShowResult)
        {
            m_expression->str("");
            m_ShowResult = false;
        }
        m_Screen->showResult(false);
    }

    bool Calc_GUIManager::init()
    {
        // Initialization flag
        bool success = true;

        // Initialize SDL
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            // Set texture filtering to linear
            if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
            {
                printf( "Warning: Linear texture filtering not enabled!" );
            }

            // Create window
            m_window = SDL_CreateWindow( "Calculator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if( m_window == NULL )
            {
                printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                // Create renderer for window
                m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                SDL_RenderSetScale(m_renderer, 0.5, 0.5);
                if( m_renderer == NULL )
                {
                    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                    success = false;
                }
                else
                {
                    // Initialize renderer color
                    SDL_SetRenderDrawColor( m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                    // Initialize PNG loading
                    int imgFlags = IMG_INIT_PNG;
                    if( !( IMG_Init( imgFlags ) & imgFlags ) )
                    {
                        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                        success = false;
                    }

                    // Initialize SDL_ttf
                    if( TTF_Init() == -1 )
                    {
                        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                        success = false;
                    }

                }
            }
        }

        return success;
    }
    bool Calc_GUIManager::load()
    {
        bool success = true;
        m_ButtonTexture = new GUI::Texture(m_renderer);

        if (!m_ButtonTexture->loadFromFile("../../assets/ButtonSpriteSheet.png"))
        {
            printf("Button sprite sheet could not be loaded!\n");
            success = false;
        }
        else
        {
            // Do the first row by hand because of clipping for parenthesis
            // then rest is done algorithmically cause I'm too lazy
            m_SpriteClips[0] = {0, 0, DEF_B_WIDTH, DEF_B_HEIGHT};
            m_SpriteClips[1] = {DEF_B_WIDTH, 0, DEF_B_WIDTH/2, DEF_B_HEIGHT};
            m_SpriteClips[2] = {DEF_B_WIDTH+DEF_B_WIDTH/2, 0, DEF_B_WIDTH/2, DEF_B_HEIGHT};
            m_SpriteClips[3] = {2*DEF_B_WIDTH, 0, DEF_B_WIDTH, DEF_B_HEIGHT};
            m_SpriteClips[4] = {3*DEF_B_WIDTH, 0, DEF_B_WIDTH, DEF_B_HEIGHT};
            for (int y = 1; y < 5; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    m_SpriteClips[(y*4+(x)) + 1] = {x*DEF_B_WIDTH, y*DEF_B_HEIGHT, DEF_B_WIDTH, DEF_B_HEIGHT};
                }
            }
            
        }

        // Probably should be finding system fonts
        m_Font = TTF_OpenFont("../../assets/calibri.ttf", 80);

        if (m_Font == NULL)
        {
            printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError);
            success = false;
        }

        m_ScreenText = new GUI::Texture(m_renderer, m_Font);
        m_ResultText = new GUI::Texture(m_renderer, m_Font);

        m_ButtonManager = new ButtonManager(m_renderer, m_ButtonTexture, m_SpriteClips, m_expression);
        m_Screen = new Screen(m_renderer, m_ScreenText, m_ResultText, m_expression, m_result);
        return success;
    }
    void Calc_GUIManager::render()
    {
        // Clear screen
        SDL_SetRenderDrawColor(m_renderer, 0x8f, 0x0b, 0x1F, 0xFF);
		SDL_RenderClear( m_renderer );

        // Render stuff
        SDL_SetRenderDrawColor(m_renderer, 0x18, 0x11, 0x11, 0xFF);
        SDL_RenderFillRect(m_renderer, &screen_rect);

		m_ButtonManager->renderAll();
        m_Screen->render();

		// Update screen
        SDL_RenderPresent( m_renderer );
    }

    void Calc_GUIManager::rerender()
    {
        if (m_ButtonManager->flag != action::NONE)
        {
            #ifdef DEBUG
            std::cout << m_expression->str() << std::endl;
            #endif
            // hide() eats up the last button press... (fix)
            if(m_ButtonManager->flag == action::RERENDER)
                hide();
            m_ButtonManager->flagHandle();
            m_Screen->update();
        }
    }
    void Calc_GUIManager::update(SDL_Event* e)
    {
        m_ButtonManager->updateAll(e);
    }
    void Calc_GUIManager::close()
    {
        // should be fine
        delete m_ButtonManager;
        delete m_Screen;

        // Destroy Textures
        m_ButtonTexture->free();
        m_ButtonTexture = NULL;

        m_ScreenText->free();
        m_ScreenText = NULL;

        m_ResultText->free();
        m_ResultText = NULL;

        TTF_CloseFont(m_Font);
        m_Font = NULL;
        //Destroy window	
        SDL_DestroyRenderer( m_renderer );
        SDL_DestroyWindow( m_window );
        m_window = NULL;
        m_renderer = NULL;

        //Quit SDL subsystems
        IMG_Quit();
        SDL_Quit();
    }
} // namespace GUI
