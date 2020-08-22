#include <ncurses.h>

void deletePrev(WINDOW *w);
void deleteNext(WINDOW *w);
void deleteCur(WINDOW *w);
void drawCur(WINDOW *W);
int getLineLength(WINDOW *w, int lineNumber);
void insertChar(WINDOW *w, chtype ch);
