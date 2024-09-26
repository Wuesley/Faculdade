// Color.cpp
#include "Color.h"
#include <cmath>

Color::Color(int nodes) {
    fillColors.resize(nodes, 0);
    fontColors.resize(nodes, 0);
}

void Color::setNodeColor(int i, int r, int g, int b) {
    fillColors[i] = b | (g << 8) | (r << 16);
    int luma = static_cast<int>(sqrt(b * b + g * g + r * r));
    luma = (luma > 240) ? 0 : 255;
    fontColors[i] = luma | (luma << 8) | (luma << 16);
}
