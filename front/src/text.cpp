#include "text.h"

void deletePrev(WINDOW *w){
    int y, x;
    getyx(w, y, x);
    wmove(w, y, x-1);
    wdelch(w);
}

void deleteNext(WINDOW *w){
    wdelch(w);
}

void deleteCur(WINDOW *w){
    wdelch(w);
}

void drawCur(WINDOW *w){
    winsch(w, '|');
}

int getLineLength(WINDOW *w, int lineNumber){
    int y,x, value;
    getyx(w, y, x);
    int lineLength = 0;
    do {
        wmove(w, lineNumber, lineLength);
        value = winch(w) & A_CHARTEXT;
        lineLength++;
    } while (value != ' ');
    wmove(w, y, x); // Return window's curser to previuos state.
    return lineLength - 1;
}

void insertChar(WINDOW *w, chtype ch){
    int y,x, value;
    getyx(w, y, x);
    winsch(w, ch);
    wmove(w, y, x+1);
}