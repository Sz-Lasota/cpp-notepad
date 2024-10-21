#include "app.hpp"

App::App(NotepadWindow *window) : window(window)
{
}

void App::handleEvents()
{
    if (queue.isEmpty())
    {
        return;
    }

    NPEvent *event = queue.poll();
    while (event != nullptr)
    {
        if (event->getEventType() == NPAppExitEvent::getStaticType())
        {
            running = false;
        }
        event = queue.poll();
    }

}

void App::run()
{
    while (running)
    {
        window->update(&queue);

        handleEvents();
    }
}
