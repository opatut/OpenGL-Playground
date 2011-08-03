#ifndef _COLOR
#define _COLOR

class Color {
public:
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
    unsigned char R, G, B, A;

    static Color White;
    static Color Black;
    static Color Red;
    static Color Green;
    static Color Blue;
    static Color Yellow;
    static Color Transparent;
};

#endif
