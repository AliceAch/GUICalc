#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "Globals.hpp"

#include "Scanner.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "Token.hpp"
#include "GUI.hpp"

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Rect gSpriteClips[20];

// Using good old raw pointers, freed by GUIManager
GUI::Texture* gButtonTexture;

void RPNprinter(std::queue<Calc::Token> output)
{
    while (!output.empty())
    {
        std::cout << output.front().stringify() << " ";
        output.pop();
    }
    std::cout << std::endl;
}

double Execute(std::string input)
{
	double result = 0;
	try
	{
		// don't have to create a new instance of each object each time we try to execute (FIX)
		Calc::Scanner scanner(input);
		Calc::Parser parser(scanner.scanTokens());
		auto output = parser.parse();
		#ifdef DEBUG
		RPNprinter(output); 
		#endif
		Calc::Interpreter interpreter;
		result = interpreter.execute(output);
		#ifdef DEBUG
		std::cout << result << std::endl;
		#endif
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return result;
}

static void run()
{
	// maybe swap out string stream for a vector of tokens (?)
	std::stringstream expression("");
	std::string result("");
	GUI::Calc_GUIManager GUIManager(&expression, &result);

	//Start up SDL and create window
	if( !GUIManager.init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if (!GUIManager.load())
		{
			printf("Failed to load!\n");
		}
		else {
			//Main loop flag
			bool quit = false;

      		GUI::ButtonManager button_m(gRenderer, gButtonTexture, gSpriteClips, &expression);

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				Uint64 start = SDL_GetPerformanceCounter();
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					GUIManager.update(&e);					
					if (GUIManager.checkFlagEXECUTE())
					{
						Execute(expression.str());
						// TEMPORARY
						// expression.str(std::to_string(Execute(expression.str())));
						result = std::to_string(Execute(expression.str()));
						// Tell GUIManager that we want to showcase the answer
						GUIManager.showcase();
					}
					GUIManager.rerender();
				}
				GUIManager.render();
			}
		}
	}

	//Free resources and close SDL
	GUIManager.close();
}

int main(int argv, char** args)
{

	run();

	return 0;
}