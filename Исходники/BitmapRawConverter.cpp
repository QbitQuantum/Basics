void BitmapRawConverter::pixelsToBitmap(char *outFilename) {
    BMP out;
    out.SetSize(width, height);
    out.SetBitDepth(24);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            out.SetPixel(i, j, getPixel(i,j));
        }
    }
    out.WriteToFile(outFilename);
}