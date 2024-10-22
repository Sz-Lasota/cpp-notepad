#include "window.hpp"

NotepadWindow::NotepadWindow(int width, int height) : width(width), height(height)
{
    display = XOpenDisplay(NULL);
    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0,
                                 0, width, height, 0, 0, 0);
    XMapWindow(display, window);
    XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask);

    deleteAtom = XInternAtom(display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(display, window, &deleteAtom, 1);

    XFlush(display);

    createGlContext();

    glXMakeCurrent(display, window, glContext);
    render();
}

NotepadWindow::~NotepadWindow()
{
    XDestroyWindow(display, window);
}

void NotepadWindow::update(EventQueue *queue)
{
    XEvent event;
    XNextEvent(display, &event);

    if (event.type == ClientMessage)
    {
        if (event.xclient.data.l[0] == deleteAtom)
        {
            queue->offer(new NPAppExitEvent());
        }
    }

    if (event.type == Expose)
    {
        width = event.xexpose.width;
        height = event.xexpose.height;
        render();
    }
}

void NotepadWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.1f, 0.5f, 0.2f, 0.9f);

    glXSwapBuffers(display, window);
}

void NotepadWindow::createGlContext()
{
    int screen_id = DefaultScreen(display);

    int attribs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

    XVisualInfo *vis_info = glXChooseVisual(display, screen_id, attribs);
    if (!vis_info)
    {
        fprintf(stderr, "No suitable OpenGL visual found\n");
        return;
    }

    glContext = glXCreateContext(display, vis_info, NULL, GL_TRUE);
    if (!glContext)
    {
        fprintf(stderr, "GL Context cannot be created!");
        return;
    }
}

void NotepadWindow::debug()
{
    std::cout << "Width: " << width << "\n";
    std::cout << "Height: " << height << "\n";
}