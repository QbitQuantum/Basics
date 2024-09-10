static void rand_color_image(LTRandomGenerator *r, int w, int h, const char *name) {
    LTImageBuffer buf(name);
    buf.width = w;
    buf.height = h;
    buf.bb_left = 0;
    buf.bb_top = h - 1;
    buf.bb_right = w - 1;
    buf.bb_bottom = 0;
    buf.bb_pixels = new LTpixel[w * h];
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            buf.bb_pixels[j * w + i] = colors[RINT(r, ncols)];
        }
    }
    ltWriteImage(name, &buf);
    printf("Generated %s\n", name);
}