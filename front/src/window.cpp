#include "window.h"
#include "text.h"
#include <iostream> 
#include <string>

int getLineLength(WINDOW *w, int lineNumber);

window::window(int nlines, int n)
{ 
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    refresh();
    curs_set(FALSE);
    this->lastLine = 0;
    this->mode = REG;
    this->waitForEscape = false;
    this->win = newwin(LINES, COLS, 0, 0);
    nodelay(this->win, TRUE);
    notimeout(this->win, TRUE);
    curs_set(WA_VERTICAL);
}

window::~window(){
    delwin(this->win);
    endwin();
}

void window::start(){
    int ch;
    drawCur(this->win);
    for (;;) {
        if ((ch = wgetch(this->win)) == ERR) {
            if(this->waitForEscape){
                // Escape
                this->switchMode(REG);
                this->waitForEscape = false;
            }
              /* user hasn't responded
               ...
              */
        }
        else {
            deleteCur(this->win);
            if(this->handleInput(ch)){
                return;
            }
            drawCur(this->win);
        }
    }
}

bool window::handleInput(int ch){
    if (ch == KEY_ESCAPE_START){
        this->waitForEscape = true;
        return false;
    }
    switch(this->mode){
        case REG:
            return this->handleRegInput(ch);
        case INSERT:
            this->handleInsertInput(ch);
    }
    return false;
}

void window::handleInsertInput(int ch){
    // wprintw(this->win, "%x", ch);
    // return;
    switch(ch){
        case KEY_ALT_BACKSPACE:
            deletePrev(this->win);
            break;
        case 0x5b337e:
            deleteNext(this->win);
            break;
        default:
            insertChar(this->win, ch);
    }
}

bool window::handleRegInput(int ch){
    bool shouldClose = false;
    int y, x, length, value;
    getyx(this->win, y, x);
    switch (ch){
        case 'q':
            shouldClose = true;
            break;
        case 'i':
            this->switchMode(INSERT);
            break;
        case 'j':
            length = getLineLength(this->win, y+1);
            y = (length != 0) ? y+1 : y;
            break;
        case 'k':
            y = (y > 0) ? y-1 : y;
            break;
        case 'l':
            length = getLineLength(this->win, y);
            x = (x > length - 1) ? x : x + 1;
            break;
        case 'h':
            x = (x > 0) ? x - 1 : x;
            break;
    }
    wmove(this->win, y, x);
    return shouldClose;
}

void window::switchMode(win_mode_t mode){
    this->mode = mode;
}
