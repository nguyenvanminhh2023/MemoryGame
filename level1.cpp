#include "showTable.h"

string Game::randomPathSticker1(int i)
{
    string path = ".png";

    int randSticker = rand() % maxStickers1;

    while (checkRandom1[randSticker] > 0)
    {
        randSticker = rand() % maxStickers1;
    }

    checkRandom1[randSticker]++;
    path.insert(0, path1[randSticker]);
    numberSticker1[i] = randSticker;
    return path;
}

void Game::makePathSticker1()
{
    for (int i = 0; i < maxStickers1; i++)
    {
        pathSticker1[i] = randomPathSticker1(i);
    }
}

int Game::mouseInPiece1(int x, int y)
{
    for (int i = 0; i < 6; i++)
    {
        if (x >= xPos1[i] && x <= (xPos1[i] + stickerSize) && y >= yPos1[i] && y <= (yPos1[i] + stickerSize)) return i;
    }
    return -1;
}

void Game::playLevel1()
{
    checkOpen = true;
    int t = mouseInPiece1(mouseX, mouseY);

    if (t != -1 && checkClick1[t] != 1)
    {
        mousePos1[stickerIsClicked] = t;
        stickerIsClicked++;
        showSticker1();
        loadSound("clickPieceSound.wav");
        checkClick1[t] = 1;
    }

    if (stickerIsClicked == 2)
    {
        moves1--;

        if (abs(numberSticker1[mousePos1[0]] - numberSticker1[mousePos1[1]]) == 3)
        {
            SDL_Delay(200);
            loadSound("correctSound.wav");
            countSticker1 += 2;
            checkOpen = true;
            pathStickerRender1[mousePos1[0]] = pathSticker1[mousePos1[0]];
            pathStickerRender1[mousePos1[1]] = pathSticker1[mousePos1[1]];
        }
        else
        {
            checkClick1[mousePos1[0]] = 0;
            checkClick1[mousePos1[1]] = 0;
            SDL_Delay(500);
            checkOpen = false;
            showSticker1();
        }
        stickerIsClicked = 0;
    }
}

void Game::showTable1(SDL_Texture* gTextureBackground, SDL_Texture* gTexturePiece)
{
    // clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gRenderer);

    // show table
    SDL_RenderCopy(gRenderer, gTextureBackground, NULL, NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Rect rect_;

    for (int i = 0; i < columns1; i++)
    {
        for (int j = 0; j < rows1; j++)
        {
            rect_.x = 295 + i*180;
            rect_.y = 280 + j*165;
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

void Game::showSticker1()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    loadImage("table1.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    string gMoves = "MOVES: ";

    if (countSticker1 == maxStickers1)
    {
        for (int i = 0; i < maxStickers1; i++)
        {
            if (pathStickerRender1[i] != "")
            {
                loadImage(pathStickerRender1[i], xPos1[i], yPos1[i], stickerSize, stickerSize);
            }
        }
        passLevel1 = true;

        for (int i = 0; i < 10; i++)
        {
            SDL_Rect viewport;
            viewport.x = (SCREEN_WIDTH - levelupw/(10 - i))/2;
            viewport.y = (SCREEN_HEIGHT - leveluph/(10 - i))/2;
            viewport.w = levelupw/(10 - i);
            viewport.h = leveluph/(10 - i);
            SDL_RenderSetViewport(gRenderer, &viewport);
            SDL_RenderCopy(gRenderer, gTextureLevelup1, NULL, NULL);
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

    if (moves1 == 0)
    {
        if (countSticker1 == maxStickers1)
        {
            for (int i = 0; i < maxStickers1; i++)
            {
                if (pathStickerRender1[i] != "")
                {
                    loadImage(pathStickerRender1[i], xPos1[i], yPos1[i], stickerSize, stickerSize);
                }
            }

            passLevel1 = true;
            for (int i = 0; i < 10; i++)
            {
                SDL_Rect viewport;
                viewport.x = (SCREEN_WIDTH - levelupw/(10 - i))/2;
                viewport.y = (SCREEN_HEIGHT - leveluph/(10 - i))/2;
                viewport.w = levelupw/(10 - i);
                viewport.h = leveluph/(10 - i);
                SDL_RenderSetViewport(gRenderer, &viewport);
                SDL_RenderCopy(gRenderer, gTextureLevelup1, NULL, NULL);
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
        gMoves = gMoves + char(moves1/10 + 48);
        gMoves = gMoves + char(moves1%10 + 48);
        loadText(gMoves);
        render(385, 58);
    }

    for (int i = 0; i < maxStickers1; i++)
    {
        if (pathStickerRender1[i] != "")
        {
            loadImage(pathStickerRender1[i], xPos1[i], yPos1[i], stickerSize, stickerSize);
        }
    }

    for (int i = 0; i < stickerIsClicked; i++)
    {
        int t = mousePos1[i];
        loadImage(pathSticker1[t], xPos1[t], yPos1[t], stickerSize, stickerSize);
    }

    if (!checkOpen)
    {
        loadImage("piece.png", xPos1[mousePos1[0]], yPos1[mousePos1[0]], stickerSize, stickerSize);
        loadImage("piece.png", xPos1[mousePos1[1]], yPos1[mousePos1[1]], stickerSize, stickerSize);
    }

    SDL_RenderPresent(gRenderer);
}


