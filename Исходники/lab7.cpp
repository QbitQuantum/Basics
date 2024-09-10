void drawBox(BMP &image, int lowx, int lowy, int highx, int highy) {

    RGBApixel redPixel;
    // make pixel red
    redPixel.Red = 255;
    redPixel.Blue = 0;
    redPixel.Green = 0;

    // color upper and bottom bounds
    for (int i = lowx; i <= highx; ++i) {
        image.SetPixel(i, lowy, redPixel);
        image.SetPixel(i, highy, redPixel);
    }
    
    // color left and right bounds
    for (int j = lowy; j <= highy; ++j) {
        image.SetPixel(lowx, j, redPixel);
        image.SetPixel(highx, j, redPixel);
    }
}