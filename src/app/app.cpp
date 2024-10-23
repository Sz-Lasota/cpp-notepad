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
            return;
        }

        if (event->getEventType() == NPKeyPressedEvent::getStaticType())
        {
            NPKeyPressedEvent* test = dynamic_cast<NPKeyPressedEvent*>(event);

            std::cout << test->keyChar << std::endl;
            delete test;
        }
        event = queue.poll();
    }
    running = true;
}

void App::run()
{
    while (running)
    {
        window->update(&queue);

        handleEvents();
    }
}
