#ifndef game_h_
#define game_h_
const int SCREEN_WIDTH  = 400;
const int SCREEN_HEIGHT = 646;
const int startX = 60;
const int startY = 55;
const int numX = 5;
const int numY = 6;
class Game
{
    bool quit = false;
    bool restart = true;
    bool played = false;
    int typeGame;
    int score[2];
    int selected[3];
    int player;
    int endGame = -1;
    int linked[2][10][10];
    int tmplink[2][10][10];
    int checked[10][10];
    int checked2[10][10];
    int frx,fry,frdr,rx,ry,rdr,sc1,sc2,scm;

    public:
        void init();
        void updateTouch(int mouseX, int mouseY);
        void update();
        void render();
        void run();
    private:
        void computerAns();
        int achieve();
        int achieve2();
        void unlinked(int dr, int i,int j);
        int getMaxScore();
        void try1(int step);
        int DFS(int i, int j);

};
#endif game_h_h;

