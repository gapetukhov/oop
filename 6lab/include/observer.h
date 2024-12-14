#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>

class Obs {
public:
    virtual void notify(const std::string& message) = 0;
    virtual ~Obs() {}
};

#endif 
