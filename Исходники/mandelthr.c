static void display_sse2(int width, int height, float xmin, float xmax, float ymin, float ymax, int yofs, int ylim)
{
    int x, y;
    int xpos, ypos;
    float xscal = (xmax - xmin) / width;
    float yscal = (ymax - ymin) / height;

    unsigned counts[4];

#if (OPTIMIZED) && 0
    __m128 ci = (__m128){ ymin, ymin, ymin, ymin };
    __m128 di = (__m128){ yscal, yscal, yscal, yscal };
#if 0
    v4sf ci = { ymin,
                ymin,
                ymin,
                ymin };
    v4sf di = { yscal, yscal, yscal, yscal };
#endif
#endif

    for (y = yofs; y < ylim; y++) {
	{
            for (ypos = 0 ; ypos < height ; ypos++) {
                for (xpos = 0; xpos < width; xpos += 4) {
                    {
                        v4sf cr = { xmin + xpos * xscal,
                                    xmin + (xpos + 1) * xscal,
                                    xmin + (xpos + 2) * xscal,
                                    xmin + (xpos + 3) * xscal };
#if (!OPTIMIZED) || 1
                        v4sf ci = { ymin + y * yscal,
                                    ymin + y * yscal,
                                    ymin + y * yscal,
                                    ymin + y * yscal };
#endif

                        mandel_sse(cr, (v4sf)ci, counts);

                        ((unsigned *) g_x11.bitmap->data)[xpos + y * width] = cols[counts[0]];
                        ((unsigned *) g_x11.bitmap->data)[xpos + 1 + y * width] = cols[counts[1]];
                        ((unsigned *) g_x11.bitmap->data)[xpos + 2 + y * width] = cols[counts[2]];
                        ((unsigned *) g_x11.bitmap->data)[xpos + 3 + y * width] = cols[counts[3]];
                    }

                    /* Display it line-by-line for speed */
                    XPutImage(g_x11.dpy, g_x11.win, g_x11.gc, g_x11.bitmap,
                              0, y, 0, y,
                              width, 1);
                }
#if (OPTIMIZED) && 0
                ci = _mm_add_ps(ci, di);
#endif
            }
        }

        XFlush(g_x11.dpy);
    }

    return;
}