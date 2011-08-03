#include "Color.hpp"

Color Color::White  = Color(255, 255, 255);
Color Color::Black  = Color(0,   0,   0);
Color Color::Red    = Color(255, 0,   0);
Color Color::Green  = Color(0,   255, 0);
Color Color::Blue   = Color(0,   0,   255);
Color Color::Yellow = Color(255, 255, 0);
Color Color::Transparent = Color(0, 0, 0, 0);

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    R = r;
    G = g;
    B = b;
    A = a;
}
