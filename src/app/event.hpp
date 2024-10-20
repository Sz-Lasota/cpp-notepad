#pragma once

#include <string>

class NPEvent {
    public:
        virtual std::string getName() = 0;
    
    protected:
        std::string name;
};

class NPWindowEvent: public NPEvent {

};