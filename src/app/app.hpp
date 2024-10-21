#pragma once

#include "../ui/window.hpp"
#include "../shared/event.hpp"
#include "../shared/datastructure.hpp"

class App
{
public:
    App(NotepadWindow *window);
    void run();

private:
    void handleEvents();
    bool running = true;


    EventQueue queue;
    NotepadWindow* window;
};