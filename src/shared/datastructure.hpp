#pragma once

#include "event.hpp"

signed int find_byte_index_by_char_index(const char *str, signed int idx);
unsigned int utf8charlen(unsigned int c);

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

class Line
{
public:
    Line *next;
    Line *prev;
    char *text;

    Line *lineAppend(Line **head, const char *text);
    void lineRemove(Line **head, Line *line);

    Line *lineAddAfter(Line *head, Line *before, const char *text);
    void lineInsert(Line *line, char *unicode, unsigned int idx);
    void LineRemoveAt(Line *line, unsigned int idx);
};