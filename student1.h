#pragma once
#include <string>
#include <vector>

struct Student {
    std::string pav;
    std::string var;
    std::vector<int> nd;
    int egz = 0;
    double galVid = 0;
    double galMed = 0;
};

enum class Mode { Vid = 1, Med = 2 };


