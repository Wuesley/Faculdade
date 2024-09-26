// Color.h
#ifndef COLOR_H
#define COLOR_H

#include <vector>

class Color {
public:
    std::vector<unsigned int> fillColors;
    std::vector<unsigned int> fontColors;

    Color(int nodes);
    void setNodeColor(int i, int r, int g, int b);
};

#endif // COLOR_H
