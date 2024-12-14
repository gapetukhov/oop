#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include "observer.h"
#include <fstream>
#include <iostream>
#include <string>

class FileObserver : public Obs {
    std::ofstream logFile;

public:
    FileObserver(const std::string& filename);
    ~FileObserver();
    void notify(const std::string& message) override;
};

#endif
