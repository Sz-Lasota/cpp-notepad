#pragma once

#include "../ui/window.hpp"

class App
{
public:
    App(NotepadWindow *window);
    void run();

private:
    NotepadWindow* window;
};