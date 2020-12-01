#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <ctime>
#include <windows.h>
#include "showTable.h"

Game Memory;

SDL_Window* gWindow = NULL;
SDL_Texture* gStart = NULL;
SDL_Texture* gStartClick = NULL;
SDL_Texture* gBackground = NULL;
SDL_Texture* gPiece = NULL;
Mix_Music* gGameMusic = NULL;
Mix_Chunk* gClickPlay = NULL;
Mix_Chunk* gClickPiece = NULL;
Mix_Chunk* gCorrect = NULL;
Mix_Chunk* gSound = NULL;

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Memory Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }

                //Initialize SDL_ttf
                if(TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
			}
		}
	}

	return success;
}

SDL_Texture* Game::loadTexture(string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool Game::loadMedia()
{
    bool success = true;

    // load texture
    gStart = loadTexture("menu.png");
    if (gStart == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

    gStartClick = loadTexture("clickPlayMenu.png");
    if (gStartClick == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

    gBackground = loadTexture("background.png");
    if (gBackground == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

    gPiece = loadTexture("piece.png");
    if (gPiece == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

    gTextureLevelup1 = loadTexture("LevelUp1.png");
    if (gTextureLevelup1 == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

    gTextureLevelup2 = loadTexture("LevelUp2.png");
    if (gTextureLevelup2 == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }

    return success;
}

void Game::loadImage(string path, int x, int y, int w, int h)
{
    gTexture = loadFromFile(path);
	SDL_Rect rect_;
    rect_.x = x;
    rect_.y = y;
    rect_.w = w;
    rect_.h = h;
    SDL_RenderCopy(gRenderer, gTexture, NULL, &rect_);
}

void Game::loadSound(string path)
{
    gSound = Mix_LoadWAV(path.c_str());
    Mix_PlayChannel(-1, gSound, 0);
}

void Game::loadText(string gMoves)
{
	gFont = TTF_OpenFont("font.ttf", 68);
	if(gFont != NULL)
	{
		SDL_Color textColor = {255, 255, 255};
		if(!Memory.loadFromRenderedText(gMoves, textColor))
		{
			printf("Failed to render text texture!\n");
		}
	}
}

void Game::close()
{
    SDL_DestroyTexture(gStart);
    gStart = NULL;
    SDL_DestroyTexture(gStartClick);
    gStartClick = NULL;
    SDL_DestroyTexture(gBackground);
    gBackground = NULL;
    SDL_DestroyTexture(gPiece);
    gPiece = NULL;

    Mix_FreeChunk(gSound);
    gSound = NULL;
    Mix_FreeMusic(gGameMusic);
    gGameMusic = NULL;

    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (Memory.init())
    {
        if (Memory.loadMedia())
        {
            srand(time(0));

            bool playGame = false;

            SDL_SetRenderDrawColor(Memory.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(Memory.gRenderer);
            Memory.loadImage("menu.png", 0, 0, Memory.SCREEN_WIDTH, Memory.SCREEN_HEIGHT);
            SDL_RenderPresent(Memory.gRenderer);

            gGameMusic = Mix_LoadMUS("gameMusic.wav");
            Mix_PlayMusic(gGameMusic, -1);

            while (!playGame)
            {
                while (SDL_PollEvent(&Memory.e) != 0)
                {
                    if (Memory.e.type == SDL_QUIT)
                    {
                        playGame = true;
                        Memory.quit = true;
                    }
                    else
                    {
                        if (!Memory.play && Memory.e.type == SDL_MOUSEMOTION)
                        {
                            if ((Memory.e.button.x >= 454 && Memory.e.button.x <= 760) && (Memory.e.button.y >= 268 && Memory.e.button.y <= 454))
                            {
                                SDL_SetRenderDrawColor(Memory.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                                SDL_RenderClear(Memory.gRenderer);
                                Memory.loadImage("clickPlayMenu.png", 0, 0, Memory.SCREEN_WIDTH, Memory.SCREEN_HEIGHT);
                                SDL_RenderPresent(Memory.gRenderer);
                            }
                            else
                            {
                                SDL_SetRenderDrawColor(Memory.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                                SDL_RenderClear(Memory.gRenderer);
                                Memory.loadImage("menu.png", 0, 0, Memory.SCREEN_WIDTH, Memory.SCREEN_HEIGHT);
                                SDL_RenderPresent(Memory.gRenderer);
                            }
                        }

                        if (!Memory.play && Memory.e.type == SDL_MOUSEBUTTONDOWN && (Memory.e.button.x >= 454 && Memory.e.button.x <= 760) && (Memory.e.button.y >= 268 && Memory.e.button.y <= 454))
                        {
                            Memory.loadSound("clickPlaySound.wav");
                            Memory.play = true;
                            SDL_SetRenderDrawColor(Memory.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                            SDL_RenderClear(Memory.gRenderer);
                            Memory.showTable1(gBackground, gPiece);
                            playGame = true;
                        }
                    }
                }
            }

            Memory.showTable1(gBackground, gPiece);

            Memory.makePathSticker1();

            while (!Memory.quit && !Memory.passLevel1)
            {
                Memory.showSticker1();

                while (SDL_PollEvent(&Memory.e) != 0)
                {
                    if (Memory.e.type == SDL_QUIT)
                    {
                        Memory.quit = true;
                    }
                    else
                    {
                        if (Memory.play && Memory.e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            Memory.mouseX = Memory.e.button.x;
                            Memory.mouseY = Memory.e.button.y;
                            Memory.playLevel1();
                        }
                    }
                }
            }

            if (Memory.passLevel1)
            {
                Memory.showTable2(gBackground, gPiece);

                Memory.makePathSticker2();

                while (!Memory.quit && !Memory.passLevel2)
                {
                    Memory.showSticker2();

                    while (SDL_PollEvent(&Memory.e) != 0)
                    {
                        if (Memory.e.type == SDL_QUIT)
                        {
                            Memory.quit = true;
                        }
                        else
                        {
                            if (Memory.play && Memory.e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                Memory.mouseX = Memory.e.button.x;
                                Memory.mouseY = Memory.e.button.y;
                                Memory.playLevel2();
                            }
                        }
                    }
                }
            }

            if (Memory.passLevel2)
            {
                Memory.showTable3(gBackground, gPiece);

                Memory.makePathSticker3();

                while (!Memory.quit)
                {
                    Memory.showSticker3();

                    while (SDL_PollEvent(&Memory.e) != 0)
                    {
                        if (Memory.e.type == SDL_QUIT)
                        {
                            Memory.quit = true;
                        }
                        else
                        {
                            if (Memory.play && Memory.e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                Memory.mouseX = Memory.e.button.x;
                                Memory.mouseY = Memory.e.button.y;
                                Memory.playLevel3();
                            }
                        }
                    }
                }
            }
        }
    }

    Memory.close();

    return 0;
}


