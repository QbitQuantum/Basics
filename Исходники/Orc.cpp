Pixel Orc::render(float luma)  {
    Pixel p;
    p.fg = makeColor(2,2,2);
    p.bg = 0;
    p.a = 0;
    p.c = toascii('O');
    return p;
}