#include "window.h"
#include <memory>

int main(){
    auto w = std::make_unique<window>(LINES, COLS);
    w->start();
}