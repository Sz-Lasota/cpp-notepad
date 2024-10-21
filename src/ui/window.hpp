#pragma once

#include <iostream>
#include <stdio.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

#include "../shared/event.hpp"
#include "../shared/datastructure.hpp"

class NotepadWindow
{
public:
    NotepadWindow(int width, int height);
    ~NotepadWindow();
    void debug();
    void update(EventQueue *queue);

private:
    int width;
    int height;

    XEvent event;

    Atom deleteAtom;

    Display *display;
    Window window;
    GLXContext glContext;

    void render();
    void createGlContext();
};
