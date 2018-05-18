#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "draw.h";
#include "game.h"
using namespace std;

void Game::init()
{
        restart = false;
        played = true;
        player = 0;
        memset(score,0,sizeof(score));
        memset(selected,-1,sizeof(selected));
        memset(linked,-1,sizeof(linked));
        memset(checked,-1,sizeof(checked));
        selected[0] = -1;
        endGame = -1;
}
int getX(int mX)
{
    for(int i = 0;i<=numX;i++)
        if(startX+i*70+10<=mX && mX<=startX+i*70+60) return i;
    for(int i = 0; i<=numX;i++)
        if (abs(startX+i*70-mX)<=12) return i;
}
int getY(int mY)
{
   for(int i = 0;i <= numY;i++)
        if(startY+i*70+10<=mY && mY<=startY+i*70+60) return i;
    for(int i = 0; i<=numY;i++)
        if (abs(startY+i*70-mY)<=12) return i;
}
void Game::updateTouch(int mouseX, int mouseY)
{
        int x = getX(mouseX);
        int y = getY(mouseY);
        if(x>=0 && y>=0 && x<=numX && y<=numY)
        {
            if(abs(startX + x*70 - mouseX)<=12) selected[0] = 1;
            else selected[0] = 0;
            selected[1] = x;
            selected[2] = y;
            if (selected[0] == 0 && x == numX-1) selected[0] = -1;
            if (selected[0] == 1 && y == numY-1) selected[0] = -1;

        }
}

int Game::achieve()
{
    int score = 0;
        for(int i = 0;i<numX;i++)
            for(int j = 0; j<numY;j++)
            if(checked[i][j] == -1 && linked[0][i][j]!=-1 && linked[1][i][j]!=-1 && linked[1][i+1][j]!=-1 && linked[0][i][j+1]!=-1)
            {
                checked[i][j] = player;
                score ++;
            }
    return score;
}
int Game::achieve2()
{
    int score = 0;
        for(int i = 0;i<numX;i++)
            for(int j = 0; j<numY;j++)

            {
                if(checked2[i][j] == -1 && tmplink[0][i][j]!=-1 && tmplink[1][i][j]!=-1 && tmplink[1][i+1][j]!=-1 && tmplink[0][i][j+1]!=-1)
                {
                    checked2[i][j] = 1;
                    score ++;
                }

            }

    return score;
}
void Game::unlinked(int dr,int i, int j)
{
    tmplink[dr][i][j] = -1;
    checked2[i][j] = -1;
    if (dr == 0) j--; else i--;
    checked2[i][j] = -1;
}
int listt[100][3];
int n;
int Game:: DFS(int i, int j)
{

        if(i>=0 && j>=0 && i<numX-1 && j<numY-1 && checked2[i][j] == -1 && tmplink[0][i][j]+tmplink[1][i][j]+tmplink[1][i+1][j]+tmplink[0][i][j+1]>=2)
        {
            checked2[i][j] = 1;

            int res = 1;
            if (tmplink[0][i][j] == -1)
            {
                tmplink[0][i][j] = 1;
                listt[n][0]=0; listt[n][1]=i;listt[n][2]=j;n++;
                res+=DFS(i,j-1);
            }
            if (tmplink[1][i][j] == -1)
            {
                tmplink[1][i][j] = 1;
                  listt[n][0]=1; listt[n][1]=i;listt[n][2]=j;n++;
                res+=DFS(i-1,j);
            }
            if (tmplink[1][i+1][j] == -1)
            {
                tmplink[1][i+1][j] = 1;
                  listt[n][0]=1; listt[n][1]=i+1;listt[n][2]=j;n++;
                res+=DFS(i+1,j);
            }
            if (tmplink[0][i][j+1] == -1)
            {
                tmplink[0][i][j+1] = 1;
                  listt[n][0]=0; listt[n][1]=i;listt[n][2]=j+1;n++;
                res+=DFS(i,j+1);
            }

            return res;

        }else return 0;
}
int Game:: getMaxScore()
{
     n = 0;
    int sc2 = 0;
    for(int x = 0; x<numX-1; x++)
        for(int y = 0; y<numY-1; y++)
        sc2 += DFS(x,y);
    for(int i = 0; i<n; i++)  unlinked(listt[i][0],listt[i][1],listt[i][2]);
    return sc2;
}

void Game::try1(int step)
{
         bool ok = true;
            for(int dr = 0; dr<2; dr++)
        for(int x = 0; x<numX-(dr==0); x++)
            for(int y = 0; y<numY-(dr==1); y++)
            if (tmplink[dr][x][y]== -1)
            {
                ok = false;
                tmplink[dr][x][y] = 1;
                if (step == 0) { rx = x; ry = y; rdr = dr;}
                 int tsc = achieve2();

                if (tsc !=0)
                {
                    sc1+=tsc;
                    try1(step+1);
                    sc1-=tsc;
                    unlinked(dr,x,y);

                }else
                {

                    sc2 = getMaxScore();

                    if (sc1-sc2>scm)
                    {

                        frx = rx;
                        fry = ry;
                        frdr = rdr;
                        scm = sc1-sc2;


                    }
                     unlinked(dr,x,y);

                }

            }
    if (ok && sc1>0)
    {
                    if (sc1>scm)
                    {
                        frx = rx;
                        fry = ry;
                        frdr = rdr;
                        scm = sc1-sc2;

                    }
    }
}
void Game::computerAns()
{
    for(int dr = 0; dr<2; dr++)
        for(int x = 0; x<numX; x++)
            for(int y = 0; y<numY; y++)
            {
            tmplink[dr][x][y] = linked[dr][x][y];
            if (tmplink[dr][x][y] !=-1) tmplink[dr][x][y] = 1;
            checked2[x][y] = checked[x][y];
            }
        sc1 = 0; sc2 = 0;scm = -1000;
    try1(0);
}
void Game::update()
{
    if(selected[0] != -1 || (typeGame == 1 && player == 1) )
    {
          if(typeGame == 1 && player == 1)
        {

            computerAns();
            selected[0] = frdr;
            selected[1] = frx;
            selected[2] = fry;

            Sleep(600);
        }
        int dr = selected[0];
        int x = selected[1];
        int y = selected[2];
        selected[0] = -1;
        if (linked[dr][x][y]!=-1) return;
        linked[dr][x][y] = player;
        int currScore = achieve();
        score[player] += currScore;
        if (currScore == 0 ){
            player = 1-player;

        }
    }

}


void Game::run()
{
    int mouseX, mouseY;
    SDL_Event e;
    initWindow();
    while( !quit )
    {
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT ) quit = true;
			if(restart)
            {
                startGame();
                played = false;
                restart = false;
            }
			if(played || ( e.type == SDL_MOUSEBUTTONDOWN && mouseX>=84 && mouseX<=318 &&mouseY>=448 && mouseY<=519)
                      || ( e.type == SDL_MOUSEBUTTONDOWN && mouseX>=84 && mouseX<=318 &&mouseY>=359 && mouseY<=426))
            {
                if(!played)
                {
                played = true;
                if ( mouseX>=84 && mouseX<=318 &&mouseY>=448 && mouseY<=519) typeGame = 2; else typeGame = 1;
                init();
                e.type = NULL;
                }
                if( played && e.type == SDL_MOUSEBUTTONDOWN && mouseX>=160 && mouseX<=214 &&mouseY>=558 && mouseY<=606)
                {
                    restart = true;

                }
                 if(e.type == SDL_MOUSEBUTTONDOWN &&  e.button.clicks == 2)
                {
                    updateTouch(mouseX,mouseY);
                    e.type = NULL;
                }



                if(endGame!=-1 && e.type == SDL_MOUSEBUTTONDOWN && mouseX>=169 && mouseX<=226 &&mouseY>=211 && mouseY<=259)
                {
                        restart = true;
                }
            }
        }
         if (played)
         {
                update();
                if(score[0] + score[1] == (numX-1)*(numY-1))
                {
                    endGame = score[0]<score[1];
                }
                render();
         }
          if( e.type == SDL_MOUSEMOTION){
                mouseX = e.button.x;
                mouseY = e.button.y;
			}
    }

	close();
}
