#include "showTable.h"

string Game::randomPathSticker3(int i)
{
    string path = ".png";

    int randSticker = rand() % maxStickers3;

    while (checkRandom3[randSticker] > 0)
    {
        randSticker = rand() % maxStickers3;
    }

    checkRandom3[randSticker]++;
    path.insert(0, path3[randSticker]);
    numberSticker3[i] = randSticker;
    return path;
}

void Game::makePathSticker3()
{
    for (int i = 0; i < maxStickers3; i++)
    {
        pathSticker3[i] = randomPathSticker3(i);
    }
}

int Game::mouseInPiece3(int x, int y)
{
    for (int i = 0; i < maxStickers3; i++)
    {
        if (x >= xPos3[i] && x <= (xPos3[i] + stickerSize) && y >= yPos3[i] && y <= (yPos3[i] + stickerSize)) return i;
    }
    return -1;
}

void Game::playLevel3()
{
    checkOpen = true;
    int t = mouseInPiece3(mouseX, mouseY);

    if (t != -1 && checkClick3[t] != 1)
    {
        mousePos3[stickerIsClicked] = t;
        stickerIsClicked++;
        showSticker3();
        loadSound("clickPieceSound.wav");
        checkClick3[t] = 1;
    }

    if (stickerIsClicked == 2)
    {
        moves3--;

        if (abs(numberSticker3[mousePos3[0]] - numberSticker3[mousePos3[1]]) == 10)
        {
            SDL_Delay(200);
            loadSound("correctSound.wav");
            countSticker3 += 2;
            checkOpen = true;
            pathStickerRender3[mousePos3[0]] = pathSticker3[mousePos3[0]];
            pathStickerRender3[mousePos3[1]] = pathSticker3[mousePos3[1]];
        }
        else
        {
            checkClick3[mousePos3[0]] = 0;
            checkClick3[mousePos3[1]] = 0;
            SDL_Delay(500);
            checkOpen = false;
            showSticker3();
        }
        stickerIsClicked = 0;
    }
}

void Game::showTable3(SDL_Texture* gTextureBackground, SDL_Texture* gTexturePiece)
{
    // clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gRenderer);

    // show table
    SDL_RenderCopy(gRenderer, gTextureBackground, NULL, NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Rect rect_;

    for (int i = 0; i < columns3; i++)
    {
        for (int j = 0; j < rows3; j++)
        {
            rect_.x = 115 + i*180;
            rect_.y = 115 + j*165;
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

void Game::showSticker3()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    loadImage("table3.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    string gMoves = "MOVES: ";

    if (countSticker3 == maxStickers3)
    {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        loadImage("win.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        loadSound("winSound.wav");
        SDL_RenderPresent(gRenderer);
        SDL_Delay(5000);
        quit = true;
        return;
    }

    if (moves3 == 0)
    {
        if (countSticker3 == maxStickers3)
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            loadImage("win.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            loadSound("winSound.wav");
            SDL_RenderPresent(gRenderer);
            SDL_Delay(5000);
            quit = true;
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
        gMoves = gMoves + char(moves3/10 + 48);
        gMoves = gMoves + char(moves3%10 + 48);
        loadText(gMoves);
        render(385, 28);
    }

    for (int i = 0; i < maxStickers3; i++)
    {
        if (pathStickerRender3[i] != "")
        {
            loadImage(pathStickerRender3[i], xPos3[i], yPos3[i], stickerSize, stickerSize);
        }
    }

    for (int i = 0; i < stickerIsClicked; i++)
    {
        int t = mousePos3[i];
        loadImage(pathSticker3[t], xPos3[t], yPos3[t], stickerSize, stickerSize);
    }

    if (!checkOpen)
    {
        loadImage("piece.png", xPos3[mousePos3[0]], yPos3[mousePos3[0]], stickerSize, stickerSize);
        loadImage("piece.png", xPos3[mousePos3[1]], yPos3[mousePos3[1]], stickerSize, stickerSize);
    }

    SDL_RenderPresent(gRenderer);
}
