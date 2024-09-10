void SkScalerContext_Windows::generatePath(const SkGlyph& glyph, SkPath* path) {



    SkAutoMutexAcquire  ac(gFTMutex);



    SkASSERT(&glyph && path);



    SkASSERT(plf);



    path->reset();



    HDC ddc = ::CreateCompatibleDC(NULL);

    SetBkMode(ddc, TRANSPARENT);



    plf->lfHeight = -SkFixedFloor(fRec.fTextSize);



    HFONT font = CreateFontIndirect(plf);

    HFONT oldfont = (HFONT)SelectObject(ddc, font);



    GLYPHMETRICS gm;



    uint32_t total_size = GetGlyphOutlineW(ddc, glyph.f_GlyphID, GGO_NATIVE, &gm, BUFFERSIZE, glyphbuf, &mat22);



    if (GDI_ERROR != total_size) {

    

        const uint8_t* cur_glyph = glyphbuf;

        const uint8_t* end_glyph = glyphbuf + total_size;

    

        while(cur_glyph < end_glyph) {

            const TTPOLYGONHEADER* th = (TTPOLYGONHEADER*)cur_glyph;

        

            const uint8_t* end_poly = cur_glyph + th->cb;

            const uint8_t* cur_poly = cur_glyph + sizeof(TTPOLYGONHEADER);

        

            path->moveTo(*(SkFixed*)(&th->pfxStart.x), *(SkFixed*)(&th->pfxStart.y));

        

            while(cur_poly < end_poly) {

                const TTPOLYCURVE* pc = (const TTPOLYCURVE*)cur_poly;

            

                if (pc->wType == TT_PRIM_LINE) {

                    for (uint16_t i = 0; i < pc->cpfx; i++) {

                        path->lineTo(*(SkFixed*)(&pc->apfx[i].x), *(SkFixed*)(&pc->apfx[i].y));

                    }

                }

            

                if (pc->wType == TT_PRIM_QSPLINE) {

                    for (uint16_t u = 0; u < pc->cpfx - 1; u++) { // Walk through points in spline

                        POINTFX pnt_b = pc->apfx[u];    // B is always the current point

                        POINTFX pnt_c = pc->apfx[u+1];

                    

                        if (u < pc->cpfx - 2) {          // If not on last spline, compute C                            

                            pnt_c.x = SkFixedToFIXED(SkFixedAve(*(SkFixed*)(&pnt_b.x), *(SkFixed*)(&pnt_c.x)));

                            pnt_c.y = SkFixedToFIXED(SkFixedAve(*(SkFixed*)(&pnt_b.y), *(SkFixed*)(&pnt_c.y)));

                        }



                        path->quadTo(*(SkFixed*)(&pnt_b.x), *(SkFixed*)(&pnt_b.y), *(SkFixed*)(&pnt_c.x), *(SkFixed*)(&pnt_c.y));

                    }

                }

                cur_poly += sizeof(uint16_t) * 2 + sizeof(POINTFX) * pc->cpfx;

            }

            cur_glyph += th->cb;

        }

    }

    else {

        SkASSERT(false);

    }



    path->close();



    ::SelectObject(ddc, oldfont);

    ::DeleteObject(font);

    ::DeleteDC(ddc);

}