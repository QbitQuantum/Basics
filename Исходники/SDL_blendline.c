static void
SDL_BlendLine_ARGB8888(SDL_Surface * dst, int x1, int y1, int x2, int y2,
                       SDL_BlendMode blendMode, Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a,
                       SDL_bool draw_end)
{
    unsigned r, g, b, a, inva;

    if (blendMode == SDL_BLENDMODE_BLEND || blendMode == SDL_BLENDMODE_ADD) {
        r = DRAW_MUL(_r, _a);
        g = DRAW_MUL(_g, _a);
        b = DRAW_MUL(_b, _a);
        a = _a;
    } else {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
    inva = (a ^ 0xff);

    if (y1 == y2) {
        switch (blendMode) {
        case SDL_BLENDMODE_BLEND:
            HLINE(Uint32, DRAW_SETPIXEL_BLEND_ARGB8888, draw_end);
            break;
        case SDL_BLENDMODE_ADD:
            HLINE(Uint32, DRAW_SETPIXEL_ADD_ARGB8888, draw_end);
            break;
        case SDL_BLENDMODE_MOD:
            HLINE(Uint32, DRAW_SETPIXEL_MOD_ARGB8888, draw_end);
            break;
        default:
            HLINE(Uint32, DRAW_SETPIXEL_ARGB8888, draw_end);
            break;
        }
    } else if (x1 == x2) {
        switch (blendMode) {
        case SDL_BLENDMODE_BLEND:
            VLINE(Uint32, DRAW_SETPIXEL_BLEND_ARGB8888, draw_end);
            break;
        case SDL_BLENDMODE_ADD:
            VLINE(Uint32, DRAW_SETPIXEL_ADD_ARGB8888, draw_end);
            break;
        case SDL_BLENDMODE_MOD:
            VLINE(Uint32, DRAW_SETPIXEL_MOD_ARGB8888, draw_end);
            break;
        default:
            VLINE(Uint32, DRAW_SETPIXEL_ARGB8888, draw_end);
            break;
        }
    } else if (ABS(x1 - x2) == ABS(y1 - y2)) {
        switch (blendMode) {
        case SDL_BLENDMODE_BLEND:
            DLINE(Uint32, DRAW_SETPIXEL_BLEND_ARGB8888, draw_end);
            break;
        case SDL_BLENDMODE_ADD:
            DLINE(Uint32, DRAW_SETPIXEL_ADD_ARGB8888, draw_end);
            break;
        case SDL_BLENDMODE_MOD:
            DLINE(Uint32, DRAW_SETPIXEL_MOD_ARGB8888, draw_end);
            break;
        default:
            DLINE(Uint32, DRAW_SETPIXEL_ARGB8888, draw_end);
            break;
        }
    } else {
        switch (blendMode) {
        case SDL_BLENDMODE_BLEND:
            AALINE(x1, y1, x2, y2,
                   DRAW_SETPIXELXY_BLEND_ARGB8888, DRAW_SETPIXELXY_BLEND_ARGB8888,
                   draw_end);
            break;
        case SDL_BLENDMODE_ADD:
            AALINE(x1, y1, x2, y2,
                   DRAW_SETPIXELXY_ADD_ARGB8888, DRAW_SETPIXELXY_ADD_ARGB8888,
                   draw_end);
            break;
        case SDL_BLENDMODE_MOD:
            AALINE(x1, y1, x2, y2,
                   DRAW_SETPIXELXY_MOD_ARGB8888, DRAW_SETPIXELXY_MOD_ARGB8888,
                   draw_end);
            break;
        default:
            AALINE(x1, y1, x2, y2,
                   DRAW_SETPIXELXY_ARGB8888, DRAW_SETPIXELXY_BLEND_ARGB8888,
                   draw_end);
            break;
        }
    }
}