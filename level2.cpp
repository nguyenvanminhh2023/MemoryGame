#include "showTable.h"

string Game::randomPathSticker2(int i)
{
    string path = ".png";

    int randSticker = rand() % maxStickers2;

    while (checkRandom2[randSticker] > 0)
    {
        randSticker = rand() % maxStickers2;
    }

    checkRandom2[randSticker]++;
    path.insert(0, path2[randSticker]);
    numberSticker2[i] = randSticker;
    return path;
}

void Game::makePathSticker2()
{
    for (int i = 0; i < maxStickers2; i++)
    {
        pathSticker2[i] = randomPathSticker2(i);
    }
}

int Game::mouseInPiece2(int x, int y)
{
    for (int i = 0; i < 12; i++)
    {
        if (x >= xPos2[i] && x <= (xPos2[i] + stickerSize) && y >= yPos2[i] && y <= (yPos2[i] + stickerSize)) return i;
    }
    return -1;
}

void Game::playLevel2()
{
    checkOpen = true;
    int t = mouseInPiece2(mouseX, mouseY);

    if (t != -1 && checkClick2[t] != 1)
    {
        mousePos2[stickerIsClicked] = t;
        stickerIsClicked++;
        showSticker2();
        loadSound("clickPieceSound.wav");
        checkClick2[t] = 1;
    }

    if (stickerIsClicked == 2)
    {
        moves2--;

        if (abs(numberSticker2[mousePos2[0]] - numberSticker2[mousePos2[1]]) == 6)
        {
            SDL_Delay(200);
            loadSound("correctSound.wav");
            countSticker2 += 2;
            checkOpen = true;
            pathStickerRender2[mousePos2[0]] = pathSticker2[mousePos2[0]];
            pathStickerRender2[mousePos2[1]] = pathSticker2[mousePos2[1]];
        }
        else
        {
            checkClick2[mousePos2[0]] = 0;
            checkClick2[mousePos2[1]] = 0;
            SDL_Delay(500);
            checkOpen = false;
            showSticker2();
        }
        stickerIsClicked = 0;
    }
}

void Game::showTable2(SDL_Texture* gTextureBackground, SDL_Texture* gTexturePiece)
{
    // clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gRenderer);

    // show table
    SDL_RenderCopy(gRenderer, gTextureBackground, NULL, NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Rect rect_;

    for (int i = 0; i < columns2; i++)
    {
        for (int j = 0; j < rows2; j++)
        {
            rect_.x = 208 + i*180;
            rect_.y = 200 + j*165;
            rect_.w = 135;
            rect_.h = 135;
            SDL_RenderSetViewport(gRenderer, &rect_);
            SDL_RenderCopy(gRenderer, gTexturePiece, NULL, NULL);
        }
    }

    rect_.x = 0;
    rect_.y = 0;
    rect_.w = SCREEN_WIDTH;
    rect_.h = SCREEN_HEIGHT;
    SDL_RenderSetViewport(gRenderer, &rect_);

    // update
    SDL_RenderPresent(gRenderer);
}

void Game::showSticker2()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    loadImage("table2.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    string gMoves = "MOVES: ";

    if (countSticker2 == 12)
    {
        for (int i = 0; i < 12; i++)
        {
            if (pathStickerRender2[i] != "")
            {
                loadImage(pathStickerRender2[i], xPos2[i], yPos2[i], stickerSize, stickerSize);
            }
        }

        passLevel2 = true;

        for (int i = 0; i < 10; i++)
        {
            SDL_Rect viewport;
            viewport.x = (SCREEN_WIDTH - levelupw/(10 - i))/2;
            viewport.y = (SCREEN_HEIGHT - leveluph/(10 - i))/2;
            viewport.w = levelupw/(10 - i);
            viewport.h = leveluph/(10 - i);
            SDL_RenderSetViewport(gRenderer, &viewport);
            SDL_RenderCopy(gRenderer, gTextureLevelup2, NULL, NULL);
            viewport.x = 0;
            viewport.y = 0;
            viewport.w = SCREEN_WIDTH;
            viewport.h = SCREEN_HEIGHT;
            SDL_RenderSetViewport(gRenderer, &viewport);
            SDL_RenderPresent(gRenderer);
            SDL_Delay(50);
        }

        SDL_Delay(3000);

        return;
    }

    if (moves2 == 0)
    {
        if (countSticker2 == maxStickers2)
        {
            for (int i = 0; i < maxStickers2; i++)
            {
                if (pathStickerRender2[i] != "")
                {
                    loadImage(pathStickerRender2[i], xPos2[i], yPos2[i], stickerSize, stickerSize);
                }
            }

            passLevel2 = true;

            for (int i = 0; i < 10; i++)
            {
                SDL_Rect viewport;
                viewport.x = (SCREEN_WIDTH - levelupw/(10 - i)) / 2;
                viewport.y = (SCREEN_HEIGHT - leveluph/(10 - i)) / 2;
                viewport.w = levelupw/(10 - i);
                viewport.h = leveluph/(10 - i);
                SDL_RenderSetViewport(gRenderer, &viewport);
                SDL_RenderCopy(gRenderer, gTextureLevelup2, NULL, NULL);
                viewport.x = 0; viewport.y = 0; viewport.w = SCREEN_WIDTH; viewport.h = SCREEN_HEIGHT;
                SDL_RenderSetViewport(gRenderer, &viewport);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(50);
            }

            SDL_Delay(3000);

            return;
        }
        else
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            loadImage("lose.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            loadSound("loseSound.wav");
            SDL_RenderPresent(gRenderer);
            SDL_Delay(5000);
            quit = true;
            return;
        }
    }
    else
    {
        gMoves = gMoves + char(moves2/10 + 48);
        gMoves = gMoves + char(moves2%10 + 48);
        loadText(gMoves);
        render(385, 48);
    }

    for (int i = 0; i < maxStickers2; i++)
    {
        if (pathStickerRender2[i] != "")
        {
            loadImage(pathStickerRender2[i], xPos2[i], yPos2[i], stickerSize, stickerSize);
        }
    }

    for (int i = 0; i < stickerIsClicked; i++)
    {
        int t = mousePos2[i];
        loadImage(pathSticker2[t], xPos2[t], yPos2[t], stickerSize, stickerSize);
    }

    if (!checkOpen)
    {
        loadImage("piece.png", xPos2[mousePos2[0]], yPos2[mousePos2[0]], stickerSize, stickerSize);
        loadImage("piece.png", xPos2[mousePos2[1]], yPos2[mousePos2[1]], stickerSize, stickerSize);
    }

    SDL_RenderPresent(gRenderer);
}




