#ifndef CONOBS_H
#define CONOBS_H

#include "observer.h"
#include <iostream>

class ConObs : public Obs {
public:
    void notify(const std::string& message) override;
};

#endif 
