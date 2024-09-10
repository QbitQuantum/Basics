void copy(BMP & InImg, BMP & OutImg, int xPos, int yPos) {
  // copy image to larger final picture so that the InImg is placed in row i, column j of OutImg
    int width = InImg.TellWidth();
    RGBApixel curPixel;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            curPixel = InImg.GetPixel(i, j);
            OutImg.SetPixel(xPos * width + i, yPos * width + j, curPixel);
        }
    }
}