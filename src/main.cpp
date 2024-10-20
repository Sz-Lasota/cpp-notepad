#include <stdio.h>

#include "main.hpp"
#include "app/app.hpp"
#include "ui/window.hpp"

int main()
{
    printf("Start\n");
    NotepadWindow *window = new NotepadWindow(WIN_W, WIN_H);

    App* app = new App(window);

    app->run();
    
    delete app;
    delete window;

    return 0;
}