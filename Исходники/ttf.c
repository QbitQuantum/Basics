font *
ttf_write_tga (char *name, int32_t pointsize)
{
    uint32_t rmask, gmask, bmask, amask;
    double glyph_per_row;
    char filename[200];
    SDL_Surface *dst;
    uint32_t height;
    uint32_t width;
    double maxx;
    double maxy[TTF_GLYPH_MAX];
    uint32_t c;
    int x;
    int y;
    double h;
    font *f;

    snprintf(filename, sizeof(filename), "%s_pointsize%u.tga",
             name, pointsize);

    if (tex_find(filename)) {
        return (0);
    }

    /*
     * x glyphs horizontally and y vertically.
     */
    glyph_per_row = 16;

    f = ttf_new(name, pointsize, TTF_STYLE_NORMAL);
    if (!f) {
        ERR("could not create font %s", name);
    }

    maxx = 0;
    memset(maxy, 0, sizeof(maxy));

    /*
     * Find the largest font glyph pointsize.
     */
    x = 0;
    y = 0;
    height = 0;

    for (c = TTF_GLYPH_MIN; c < TTF_GLYPH_MAX; c++) {

        if (f->tex[c].image) {
            maxx = max(maxx, f->tex[c].image->w);
            maxy[y] = max(maxy[y], f->tex[c].image->h);
        }

        if (++x >= glyph_per_row) {
            x = 0;
            height += maxy[y];
            y++;
        }
    }

    if (!maxx) {
        ERR("no glyphs in font %s", name);
    }

    width = glyph_per_row * maxx;

    if (MULTIPLE_BITS(width)) {
        width = nextpoweroftwo(width);
    }

    height += 40;

    if (MULTIPLE_BITS(height)) {
        height = nextpoweroftwo(height);
    }

    /*
     * Make a large surface for all glyphs.
     */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    dst = SDL_CreateRGBSurface(0, width, height, 32,
                               rmask, gmask, bmask, amask);
    if (!dst) {
        ERR("no surface created for size %dx%d font %s", width, height, name);
    }

    newptr(dst, "SDL_CreateRGBSurface");

    /*
     * Blit each glyph to the large surface.
     */
    x = 0;
    y = 0;
    h = 0;

    for (c = TTF_GLYPH_MIN; c < TTF_GLYPH_MAX; c++) {

        if (f->tex[c].image) {
            SDL_Rect dstrect = { maxx * x, h, maxx, maxy[y] };

            SDL_BlitSurface(f->tex[c].image, 0, dst, &dstrect);
        }

        if (++x >= glyph_per_row) {
            x = 0;
            h += maxy[y];
            y++;
        }
    }

    /*
     * Convert the black border smoothing that ttf adds into alpha.
     */
    {
        double x;
        double y;

        for (x = 0; x < dst->w; x++) {
            for (y = 0; y < dst->h; y++) {

                color c;

                c = getPixel(dst, x, y);

                if ((c.a == 255) &&
                    (c.r == 255) &&
                    (c.g == 255) &&
                    (c.b == 255)) {
                    /*
                     * Do nothing.
                     */
                } else if ((c.a == 0) &&
                    (c.r == 0) &&
                    (c.g == 0) &&
                    (c.b == 0)) {
                    /*
                     * Do nothing.
                     */
                } else {
                    /*
                     * Convery gray to white with alpha.
                     */
                    c.a = (c.r + c.g + c.b) / 3;
                    c.r = 255;
                    c.g = 255;
                    c.b = 255;
                }

                putPixel(dst, x, y, c);
            }
        }
    }

#define MAX_TEXTURE_HEIGHT 4096

    if (dst->h > MAX_TEXTURE_HEIGHT) {
        ERR("ttf is too large");
    }

    uint8_t filled_pixel_row[MAX_TEXTURE_HEIGHT] = {0};

    /*
     * What the hell am I doing here? The ttf library returns incorrect
     * boounds for the top and bottom of glyphs, so I'm looking for a line of
     * no pixels above and below each glyph so I can really find the texture
     * bounds of a glyph. This allows squeezing of text together.
     */
    {
        int x;
        int y;

        for (y = 0; y < dst->h; y++) {
            for (x = 0; x < dst->w; x++) {
                color c;
                c = getPixel(dst, x, y);
                if (c.r || c.g || c.b || c.a) {
                    filled_pixel_row[y] = true;
                    break;
                }
            }
        }
    }

    /*
     * Work our the tex co-ords for each glyph in the large tex.
     */
    x = 0;
    y = 0;
    h = 0;

    int d1_max = 0;
    int d2_max = 0;

    for (c = TTF_GLYPH_MIN; c < TTF_GLYPH_MAX; c++) {

        {
            int y = (h + (h + f->glyphs[c].height)) / 2;

            int miny = y;
            int maxy = y;

            for (;;) {
                if (!filled_pixel_row[miny]) {
                    break;
                }

                miny--;
                if (miny <= 0) {
                    break;
                }
            }

            for (;;) {
                if (!filled_pixel_row[maxy]) {
                    break;
                }

                maxy++;
                if (maxy >= MAX_TEXTURE_HEIGHT - 1) {
                    break;
                }
            }

            int d1 = y - miny;
            if (d1 > d1_max) {
                d1_max = d1;
            }

            int d2 = maxy - y;
            if (d2 > d2_max) {
                d2_max = d2;
            }
        }

        if (++x >= glyph_per_row) {
            x = 0;
            h += maxy[y];
            y++;
        }
    }

    x = 0;
    y = 0;
    h = 0;

    for (c = TTF_GLYPH_MIN; c < TTF_GLYPH_MAX; c++) {

        f->glyphs[c].texMinX =
                        (double)(x * maxx) / (double)dst->w;
        f->glyphs[c].texMaxX =
                        (double)((x * maxx) + f->glyphs[c].width) /
                        (double)dst->w;

        {
            int y = (h + (h + f->glyphs[c].height)) / 2;

            int y1 = y - d1_max;
            int y2 = y + d2_max;

            if (y1 < 0) {
                y1 = 0;
            }

            f->glyphs[c].texMinY =
                            (double)(y1) /
                            (double)dst->h;
            f->glyphs[c].texMaxY =
                            (double)(y2) /
                            (double)dst->h;
        }

        if (++x >= glyph_per_row) {
            x = 0;
            h += maxy[y];
            y++;
        }
    }

    SDL_LockSurface(dst);
    stbi_write_tga(filename, dst->w, dst->h, STBI_rgb_alpha, dst->pixels);
    SDL_UnlockSurface(dst);

    texp tex;
    tex = tex_from_surface(dst, filename, filename);
    if (!tex) {
        ERR("could not convert %s to tex", filename);
    }

    /*
     * Work our the tex co-ords for each glyph in the large tex.
     */
    x = 0;
    y = 0;
    h = 0;

    for (c = TTF_GLYPH_MIN; c < TTF_GLYPH_MAX; c++) {

        f->tex[c].image = dst;
        f->tex[c].tex = tex_get_gl_binding(tex);
    }

    /*
     * Save the glyph data.
     */
    snprintf(filename, sizeof(filename), "%s_pointsize%u.data",
             name, pointsize);

    FILE *out = fopen(filename, "w");

    fwrite(f->glyphs, sizeof(f->glyphs), 1, out);

    fclose(out);

    printf("wrote %s\n",filename);
    return (f);
}