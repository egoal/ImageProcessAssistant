#pragma once

#include <string>
// global data, macros

class GD{
    GD();
public:
    static GD* getInstance();

    void initFromFile();
    void updateToFile();

    std::string currentFileName{""};

    std::string lastOpenFolder;
    std::string lastSaveFolder;

    const std::string contourResultFile =   "./contours_result.txt";

private:
    std::string initfile{"./gd.txt"};
};
