#ifndef draw_h_
#define draw_h_
void initWindow();
void loadMedia(std::string path,int x,int y, int w, int h);
void drawVertical(int i, int j,int color);
void drawHorizontal(int i,int j, int color);
void drawBoxes(int i, int j,int color);
void drawScore(int score, int player);
void startGame();
void close();
#endif draw_h_h;
