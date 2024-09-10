/**
 * This method checks to see if the given LCD glyph bounds fall within the
 * cached destination texture bounds.  If so, this method can return
 * immediately.  If not, this method will copy a chunk of framebuffer data
 * into the cached destination texture and then update the current cached
 * destination bounds before returning.
 */
static void
OGLTR_UpdateCachedDestination(OGLSDOps *dstOps, GlyphInfo *ginfo,
                              jint gx1, jint gy1, jint gx2, jint gy2,
                              jint glyphIndex, jint totalGlyphs)
{
    jint dx1, dy1, dx2, dy2;
    jint dx1adj, dy1adj;

    if (isCachedDestValid && INSIDE(gx1, gy1, gx2, gy2, cachedDestBounds)) {
        // glyph is already within the cached destination bounds; no need
        // to read back the entire destination region again, but we do
        // need to see if the current glyph overlaps the previous glyph...

        if (INTERSECTS(gx1, gy1, gx2, gy2, previousGlyphBounds)) {
            // the current glyph overlaps the destination region touched
            // by the previous glyph, so now we need to read back the part
            // of the destination corresponding to the previous glyph
            dx1 = previousGlyphBounds.x1;
            dy1 = previousGlyphBounds.y1;
            dx2 = previousGlyphBounds.x2;
            dy2 = previousGlyphBounds.y2;

            // this accounts for lower-left origin of the destination region
            dx1adj = dstOps->xOffset + dx1;
            dy1adj = dstOps->yOffset + dstOps->height - dy2;

            // copy destination into subregion of cached texture tile:
            //   dx1-cachedDestBounds.x1 == +xoffset from left side of texture
            //   cachedDestBounds.y2-dy2 == +yoffset from bottom of texture
            j2d_glActiveTextureARB(GL_TEXTURE1_ARB);
            j2d_glCopyTexSubImage2D(GL_TEXTURE_2D, 0,
                                    dx1 - cachedDestBounds.x1,
                                    cachedDestBounds.y2 - dy2,
                                    dx1adj, dy1adj,
                                    dx2-dx1, dy2-dy1);
        }
    } else {
        jint remainingWidth;

        // destination region is not valid, so we need to read back a
        // chunk of the destination into our cached texture

        // position the upper-left corner of the destination region on the
        // "top" line of glyph list
        // REMIND: this isn't ideal; it would be better if we had some idea
        //         of the bounding box of the whole glyph list (this is
        //         do-able, but would require iterating through the whole
        //         list up front, which may present its own problems)
        dx1 = gx1;
        dy1 = gy1;

        if (ginfo->advanceX > 0) {
            // estimate the width based on our current position in the glyph
            // list and using the x advance of the current glyph (this is just
            // a quick and dirty heuristic; if this is a "thin" glyph image,
            // then we're likely to underestimate, and if it's "thick" then we
            // may end up reading back more than we need to)
            remainingWidth =
                (jint)(ginfo->advanceX * (totalGlyphs - glyphIndex));
            if (remainingWidth > OGLTR_CACHED_DEST_WIDTH) {
                remainingWidth = OGLTR_CACHED_DEST_WIDTH;
            } else if (remainingWidth < ginfo->width) {
                // in some cases, the x-advance may be slightly smaller
                // than the actual width of the glyph; if so, adjust our
                // estimate so that we can accomodate the entire glyph
                remainingWidth = ginfo->width;
            }
        } else {
            // a negative advance is possible when rendering rotated text,
            // in which case it is difficult to estimate an appropriate
            // region for readback, so we will pick a region that
            // encompasses just the current glyph
            remainingWidth = ginfo->width;
        }
        dx2 = dx1 + remainingWidth;

        // estimate the height (this is another sloppy heuristic; we'll
        // make the cached destination region tall enough to encompass most
        // glyphs that are small enough to fit in the glyph cache, and then
        // we add a little something extra to account for descenders
        dy2 = dy1 + OGLTR_CACHE_CELL_HEIGHT + 2;

        // this accounts for lower-left origin of the destination region
        dx1adj = dstOps->xOffset + dx1;
        dy1adj = dstOps->yOffset + dstOps->height - dy2;

        // copy destination into cached texture tile (the lower-left corner
        // of the destination region will be positioned at the lower-left
        // corner (0,0) of the texture)
        j2d_glActiveTextureARB(GL_TEXTURE1_ARB);
        j2d_glCopyTexSubImage2D(GL_TEXTURE_2D, 0,
                                0, 0, dx1adj, dy1adj,
                                dx2-dx1, dy2-dy1);

        // update the cached bounds and mark it valid
        cachedDestBounds.x1 = dx1;
        cachedDestBounds.y1 = dy1;
        cachedDestBounds.x2 = dx2;
        cachedDestBounds.y2 = dy2;
        isCachedDestValid = JNI_TRUE;
    }

    // always update the previous glyph bounds
    previousGlyphBounds.x1 = gx1;
    previousGlyphBounds.y1 = gy1;
    previousGlyphBounds.x2 = gx2;
    previousGlyphBounds.y2 = gy2;
}