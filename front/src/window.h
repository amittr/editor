#include <ncurses.h>

#define KEY_ESCAPE_START 27
#define KEY_ALT_BACKSPACE 127

enum win_mode_t {
    REG,
    INSERT,
    VISUAL,
};


class window
{
private:
    int ncols;
    int nlines;
    WINDOW *win;
    bool waitForEscape;
    win_mode_t mode;
    int lastLine;

    // Handlers
    void switchMode(win_mode_t mode);
    bool handleInput(int ch);
    bool handleRegInput(int ch);
    void handleInsertInput(int ch);
    bool handleVisualInput(int ch);
public:
    window(int nlines, int ncols);
    ~window();
    void start();
};

