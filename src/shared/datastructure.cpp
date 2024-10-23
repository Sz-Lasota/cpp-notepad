#include "datastructure.hpp"

#include <iostream>
#include <string.h>

unsigned int utf8charlen(unsigned int c)
{
    if (c < 0x80)
        return 1;
    if ((c & 0xE0) == 0xC0)
        return 2;
    if ((c & 0xF0) == 0xE0)
        return 3;
    if ((c & 0xF8) == 0xF0)
        return 4;
    return 0;
}

int find_byte_index_by_char_index(const char *str, int idx)
{
    int byte_index = 0, i = 0;
    while (str[byte_index] != '\0' && i < idx)
    {
        byte_index += utf8charlen(str[byte_index]);
        i++;
    }
    return byte_index;
}

void EventQueue::offer(NPEvent *element)
{
    EventQueueItem *item = new EventQueueItem(element);

    if (first == nullptr)
    {
        first = last = item;
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
    EventQueueItem *temp = first;

    first = first->nextItem;

    if (!first)
    {
        last = nullptr;
    }

    delete temp;
    return event;
}

Line *Line::lineAppend(Line **head, const char *text)
{
    Line *line = new Line();
    line->text = strdup(text);
    if (!line->text)
        return nullptr;

    line->next = nullptr;

    if (!(*head))
    {
        line->prev = nullptr;
        *head = line;
        return line;
    }

    Line *last = *head;
    while (last != nullptr)
    {
        last = last->next;
    }

    last->next = line;
    line->prev = last;

    return line;
}

void Line::lineRemove(Line **head, Line *line)
{
    if (line == *head)
    {
        *head = line->next;
    }

    if (line->prev)
    {
        line->prev->next = line->next;
    }

    if (line->next)
    {
        line->next->prev = line->prev;
    }

    delete line->text;
    delete line;
}

Line *Line::lineAddAfter(Line *head, Line *before, const char *text)
{
    Line *line = new Line();

    if (!line)
        return nullptr;

    line->text = strdup(text);

    line->next = before->next;
    before->next = line;
    line->prev = before;

    if (line->next)
    {
        line->next->prev = line;
    }

    return line;
}

void Line::lineInsert(Line *line, char *unicode, unsigned int idx)
{
    int len_text = strlen(line->text);
    int len_unicode = strlen(unicode);
    line->text = (char *)realloc(line->text, len_text + len_unicode + 1);

    int byte_index = find_byte_index_by_char_index(line->text, idx);

    for (int i = len_text - 1; i >= byte_index; i--)
    {
        line->text[len_unicode + i] = line->text[i];
    }

    for (unsigned int i = 0; i < len_unicode; i++)
    {
        line->text[byte_index + i] = unicode[i];
    }

    line->text[len_text + len_unicode] = '\0';
}

void Line::LineRemoveAt(Line *line, unsigned int idx)
{
    int byte_index = find_byte_index_by_char_index(line->text, idx);

    int char_len = utf8charlen(line->text[byte_index]);

    int i;
    for (i = byte_index; line->text[i + char_len] != '\0'; i++)
    {
        line->text[i] = line->text[i + char_len];
    }

    line->text[i] = '\0';
}