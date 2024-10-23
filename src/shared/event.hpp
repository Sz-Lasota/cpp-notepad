#pragma once

#include <string>
#include <functional>
#include <iostream>

enum class NPEventType
{
    NoneEvent = 0,
    AppExit,
    AppResize,
    ModuleResize,
    KeyPressed
};

enum NPEventCategory
{
    NoneEvent = 0,
    AppEvent = (1 << 0),
    KeyboardEvent = (1 << 1),
};

class NPEvent
{
public:
    virtual NPEventType getEventType() const = 0;
    virtual int getCategoryFlag() const = 0;

private:
    inline bool isInCategory(NPEventCategory category)
    {
        return getCategoryFlag() & category;
    }
};

class NPAppExitEvent : public NPEvent
{
public:
    static NPEventType getStaticType() { return NPEventType::AppExit; }
    virtual NPEventType getEventType() const override { return getStaticType(); }
    virtual int getCategoryFlag() const override { return KeyboardEvent; }
};

class NPKeyPressedEvent : public NPEvent
{
public:
    static NPEventType getStaticType() { return NPEventType::KeyPressed; }
    virtual NPEventType getEventType() const override { return getStaticType(); }
    virtual int getCategoryFlag() const override { return KeyboardEvent; }
    char keyChar[32];
};

class NPEventDispatcher
{
    template <typename T>
    using NPEventHandler = std::function<bool(T &)>;

public:
    NPEventDispatcher(NPEvent &event) : event(event) {}

    template <typename T>
    bool handle(NPEventHandler<T> handler)
    {
        if (event.getEventType() == T::getStaticType())
        {
            handler(*(T *)&event);
            return true;
        }

        return false;
    }

private:
    NPEvent &event;
};