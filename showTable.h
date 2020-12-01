#ifndef SHOW_TABLE_H
#define SHOW_TABLE_H

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

using namespace std;

class Game
{
public:
    Game();
    ~Game();
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 800;
    const int columns1 = 3, columns2 = 4, columns3 = 5;
    const int rows1 = 2, rows2 = 3, rows3 = 4;
    const int levelupw = 800, leveluph = 800;
    bool play = false;
    bool passLevel1 = false;
    bool passLevel2 = false;
    string pathStickerRender1[6], pathStickerRender2[12], pathStickerRender3[20];
    bool quit = false;
    SDL_Event e;
    SDL_Renderer* gRenderer;
    Mix_Music* gMusic;
    int moves1 = 8, moves2 = 15, moves3 = 25;
    int mouseX, mouseY;
    void makePathSticker1();
    void makePathSticker2();
    void makePathSticker3();
    void showSticker1();
    void showSticker2();
    void showSticker3();
    void playLevel1();
    void playLevel2();
    void playLevel3();
    void loadImage(string path, int x, int y, int w, int h);
    void loadSound(string path);
    bool init();
    bool loadMedia();
    void showTable1(SDL_Texture* gTextureBackground, SDL_Texture* gTexturePiece);
    void showTable2(SDL_Texture* gTextureBackground, SDL_Texture* gTexturePiece);
    void showTable3(SDL_Texture* gTextureBackground, SDL_Texture* gTexturePiece);
    SDL_Texture* loadTexture(string path);
    void close();

private:
    SDL_Texture* mTexture;
    SDL_Texture* gTextureLevelup1;
    SDL_Texture* gTextureLevelup2;
    int mWidth;
    int mHeight;
    const int maxStickers1 = 6;
    const int maxStickers2 = 12;
    const int maxStickers3 = 20;
    const string path1[6] = {"1", "2", "3", "11", "12", "13"};
    const string path2[12] = {"4", "5", "6", "7", "8", "9", "14", "15", "16", "17", "18", "19"};
    const string path3[20] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
    const int xPos1[6] = {295, 475, 655, 295, 475, 655};
    const int yPos1[6] = {280, 280, 280, 445, 445, 445};
    const int xPos2[12] = {208, 388, 568, 748, 208, 388, 568, 748, 208, 388, 568, 748};
    const int yPos2[12] = {200, 200, 200, 200, 365, 365, 365, 365, 530, 530, 530, 530};
    const int xPos3[20] = {115, 295, 475, 655, 835, 115, 295, 475, 655, 835, 115, 295, 475, 655, 835, 115, 295, 475, 655, 835};
    const int yPos3[20] = {115, 115, 115, 115, 115, 280, 280, 280, 280, 280, 445, 445, 445, 445, 445, 610, 610, 610, 610, 610};
    const int stickerSize = 135;
    string pathSticker1[6], pathSticker2[12], pathSticker3[20];
    int checkRandom1[6] = {0};
    int checkRandom2[12] = {0};
    int checkRandom3[20] = {0};
    int mousePos1[2], mousePos2[2], mousePos3[2];
    int numberSticker1[6], numberSticker2[12], numberSticker3[20];
    int stickerIsClicked = 0;
    bool checkOpen = false;
    int checkClick1[6] = {0};
    int checkClick2[12] = {0};
    int checkClick3[20] = {0};
    SDL_Window* gWindow;
    SDL_Texture* gTexture;
    SDL_Point mPosition;
    Mix_Chunk* gSound = NULL;
    TTF_Font* gFont = NULL;
    int countSticker1 = 0, countSticker2 = 0, countSticker3 = 0;
    string randomPathSticker1(int i);
    string randomPathSticker2(int i);
    string randomPathSticker3(int i);
    int mouseInPiece1(int x, int y);
    int mouseInPiece2(int x, int y);
    int mouseInPiece3(int x, int y);
    SDL_Texture* loadFromFile(string path);
    bool loadFromRenderedText(string textureText, SDL_Color textColor);
    void loadText(string gMoves);
    void free();
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth();
    int getHeight();
};



#endif // SHOW_TABLE_H
