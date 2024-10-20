#include "app.hpp"

App::App(NotepadWindow *window) : window(window)
{
}

void App::run()
{
    bool running = true;
    while (running)
    {

        window->update(&running);
    }
}
