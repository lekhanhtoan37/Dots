#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "game.h"
using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture[10];
SDL_Surface* surface[10];
TTF_Font *font = NULL;

void initWindow()
{
	if( SDL_Init( SDL_INIT_VIDEO ) >= 0 )
	{
		window = SDL_CreateWindow( "DOTS AND BOXES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window != NULL )
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer != NULL )
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		}
	}
	surface[0] = IMG_Load("background.png");
	texture[0] = SDL_CreateTextureFromSurface( renderer, surface[0] );
	surface[1] = IMG_Load("redH.png");
	texture[1] = SDL_CreateTextureFromSurface( renderer, surface[1] );
	surface[2] = IMG_Load("blueH.png");
	texture[2] = SDL_CreateTextureFromSurface( renderer, surface[2] );
	surface[3] = IMG_Load("redV.png");
	texture[3] = SDL_CreateTextureFromSurface( renderer, surface[3] );
	surface[4] = IMG_Load("blueV.png");
	texture[4] = SDL_CreateTextureFromSurface( renderer, surface[4] );
	surface[5] = IMG_Load("red.png");
	texture[5] = SDL_CreateTextureFromSurface( renderer, surface[5] );
	surface[6] = IMG_Load("blue.png");
	texture[6] = SDL_CreateTextureFromSurface( renderer, surface[6] );
	surface[7] = IMG_Load("start.png");
	texture[7] = SDL_CreateTextureFromSurface( renderer, surface[7] );
	surface[8] = IMG_Load("redWin.png");
	texture[8] = SDL_CreateTextureFromSurface( renderer, surface[8] );
	surface[9] = IMG_Load("blueWin.png");
	texture[9] = SDL_CreateTextureFromSurface( renderer, surface[9] );
    TTF_Init();
    font = TTF_OpenFont("font3.ttf",60);

}

void loadMedia(int ob,int x,int y)
{
	SDL_Rect dest = {x, y,surface[ob]->w,surface[ob]->h};

    SDL_RenderCopy(renderer, texture[ob], NULL, &dest);
}
void drawHorizontal(int i,int j, int color)
{
    loadMedia(color + 1,startX+12+i*48+11*(2*i),startY-8+j*70);
}
void drawVertical(int i, int j,int color)
{
    loadMedia(color+3,startX-6+i*48+11*(2*i),startY+11+j*70);
}
void drawBoxes(int i, int j,int color)
{
    loadMedia(color + 5,startX+8+i*48+11*(2*i),startY+6+j*70);
}
void drawScore(int score, int player)
{

    SDL_Color textColor;
    if (player == 1) textColor = {0,0,255};
    else textColor = {255,0,0};

    char buffer[2];
    itoa(score,buffer,10);
    string text = string(buffer);
   if (score<10) text = "0"+text;

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(),textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_Rect dest;
    if (player == 0) dest.x = 88; else dest.x = 251;
    dest.y = 460;
    dest.w = surface->w;
    dest.h = surface->h;
     SDL_RenderCopy(renderer, texture, NULL, &dest);
     SDL_DestroyTexture(texture);
     SDL_FreeSurface(surface);


}
void startGame()
{
    loadMedia(7,0,0);
     SDL_RenderPresent(renderer);
}
void Game::render()
{
   // if (player == 1 && typeGame == 1)  Sleep(700);
    if (endGame == -1)
    {

    loadMedia(0,0,0);
    for(int i = 0; i<numX; i++)
        for(int j = 0; j<numY; j++)
        {
            if (linked[1][i][j]!=-1) drawVertical(i,j,linked[1][i][j]);
             if (linked[0][i][j]!=-1) drawHorizontal(i,j,linked[0][i][j]);
            if (checked[i][j]!=-1) drawBoxes(i,j,checked[i][j]);
        }
    drawScore(score[0],0);
    drawScore(score[1],1);
    }
    else
    {
        loadMedia(endGame+8,0,0);
        drawScore(score[0],0);
        drawScore(score[1],1);
    }
    SDL_RenderPresent(renderer);

}
void close()
{
	for(int i = 0; i<10;i++)
	SDL_DestroyTexture( texture[i] );
	for(int i = 0; i<10;i++)
    SDL_FreeSurface(surface[i]);
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

