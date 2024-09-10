// Test ImageBuf::zero and ImageBuf::fill
void ImageBuf_zero_fill ()
{
    const int WIDTH = 8;
    const int HEIGHT = 6;
    const int CHANNELS = 4;
    ImageSpec spec (WIDTH, HEIGHT, CHANNELS, TypeDesc::FLOAT);
    spec.alpha_channel = 3;

    // Create a buffer -- pixels should be undefined
    ImageBuf A ("A", spec);
    
    // Set a pixel to an odd value, make sure it takes
    const float arbitrary1[CHANNELS] = { 0.2, 0.3, 0.4, 0.5 };
    A.setpixel (1, 1, arbitrary1);
    float pixel[CHANNELS];   // test pixel
    A.getpixel (1, 1, pixel);
    for (int c = 0;  c < CHANNELS;  ++c)
        OIIO_CHECK_EQUAL (pixel[c], arbitrary1[c]);

    // Zero out and test that it worked
    ImageBufAlgo::zero (A);
    for (int j = 0;  j < HEIGHT;  ++j) {
        for (int i = 0;  i < WIDTH;  ++i) {
            float pixel[CHANNELS];
            A.getpixel (i, j, pixel);
            for (int c = 0;  c < CHANNELS;  ++c)
                OIIO_CHECK_EQUAL (pixel[c], 0.0f);
        }
    }

    // Test fill of whole image
    const float arbitrary2[CHANNELS] = { 0.6, 0.7, 0.3, 0.9 };
    ImageBufAlgo::fill (A, arbitrary2);
    for (int j = 0;  j < HEIGHT;  ++j) {
        for (int i = 0;  i < WIDTH;  ++i) {
            float pixel[CHANNELS];
            A.getpixel (i, j, pixel);
            for (int c = 0;  c < CHANNELS;  ++c)
                OIIO_CHECK_EQUAL (pixel[c], arbitrary2[c]);
        }
    }

    // Test fill of partial image
    const float arbitrary3[CHANNELS] = { 0.42, 0.43, 0.44, 0.45 };
    {
        const int xbegin = 3, xend = 5, ybegin = 0, yend = 4;
        ImageBufAlgo::fill (A, arbitrary3, xbegin, xend, ybegin, yend);
        for (int j = 0;  j < HEIGHT;  ++j) {
            for (int i = 0;  i < WIDTH;  ++i) {
                float pixel[CHANNELS];
                A.getpixel (i, j, pixel);
                if (j >= ybegin && j < yend && i >= xbegin && i < xend) {
                    for (int c = 0;  c < CHANNELS;  ++c)
                        OIIO_CHECK_EQUAL (pixel[c], arbitrary3[c]);
                } else {
                    for (int c = 0;  c < CHANNELS;  ++c)
                        OIIO_CHECK_EQUAL (pixel[c], arbitrary2[c]);
                }
            }
        }
    }
}