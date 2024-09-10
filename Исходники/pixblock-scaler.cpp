/** Calculates cubically interpolated value of the four given pixel values.
 * The pixel values should be interpolated values from sampley, from four
 * horizontally adjacent vertical lines. The parameters a, b, c and d
 * should be in fixed point format with 8-bit decimal part.
 * If we are calculating a pixel, whose x-coordinate in source image is
 * i, these vertical  lines from where a, b, c and d are calculated, should be
 * floor(i) - 1, floor(i), floor(i) + 1, floor(i) + 2, respectively.
 * Parameter len should be set to i.
 * Returns the interpolated value in 8-bit format, ready to be written
 * to output buffer.
 */
inline static int samplex(const int a, const int b, const int c, const int d, const double len) {
    double lenf = len - floor(len);
    int sum = 0;
    sum += (int)(a * (((-1.0 / 3.0) * lenf + 4.0 / 5.0) * lenf - 7.0 / 15.0) * lenf);
    sum += (int)(b * (((lenf - 9.0 / 5.0) * lenf - 1.0 / 5.0) * lenf + 1.0));
    sum += (int)(c * ((((1 - lenf) - 9.0 / 5.0) * (1 - lenf) - 1.0 / 5.0) * (1 - lenf) + 1.0));
    sum += (int)(d * (((-1.0 / 3.0) * (1 - lenf) + 4.0 / 5.0) * (1 - lenf) - 7.0 / 15.0) * (1 - lenf));
    //if (sum < 0) sum = 0;
    //if (sum > 255 * 256) sum = 255 * 256;
    return sum / 256;
}