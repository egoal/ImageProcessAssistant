#pragma once

#include <string>
// global data, macros

class GD{
    GD();
public:
    static GD* getInstance();

    void initFromFile();
    void updateToFile();

    std::string lastOpenFolder;
    std::string lastSaveFolder;
private:
    std::string initfile{"./gd.txt"};
};
