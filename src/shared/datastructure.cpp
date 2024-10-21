#include "datastructure.hpp"

#include <iostream>


void EventQueue::offer(NPEvent *element)
{
    EventQueueItem *item = new EventQueueItem(element);

    if (first == nullptr)
    {
        std::cout << "here" << std::endl;
        first = last = item;
        std::cout << "here" << std::endl;

        return;
    }
    last->nextItem = item;
    last = item;
}

NPEvent *EventQueue::peak()
{
    if (!first)
    {
        return nullptr;
    }
    return first->unwrap();
}

NPEvent *EventQueue::poll()
{
    if (!first)
    {
        return nullptr;
    }

    NPEvent *event = first->unwrap();

    first = first->nextItem;

    if (!first)
    {
        last = nullptr;
    }

    return event;
}