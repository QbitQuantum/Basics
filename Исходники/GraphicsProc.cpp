bool DDADraw(int x0, int y0, int xEnd, int yEnd, int width, int height, float* PixelBuffer, float red, float green, float blue)
{
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;
    if (x0 < 0 || y0 < 0 || xEnd > width || yEnd > height)
        return false;

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    setPixel(PixelBuffer, round(x), round(y), width, height, red, blue, green);
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        setPixel(PixelBuffer, round(x), round(y), width, height, red, blue, green);
    }
    return true;
}