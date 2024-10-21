#pragma once

#include "event.hpp"

class EventQueueItem
{
public:
    EventQueueItem(NPEvent *event) : event(event)
    {
        nextItem = nullptr;
    }
    inline NPEvent *unwrap() { return event; }
    EventQueueItem *nextItem;

private:
    NPEvent *event;
};

class EventQueue
{
public:
    EventQueue() { first = last = nullptr; }
    NPEvent *poll();
    NPEvent *peak();
    void offer(NPEvent *element);
    inline bool isEmpty() { return first == nullptr; }

private:
    EventQueueItem *first;
    EventQueueItem *last;
};
