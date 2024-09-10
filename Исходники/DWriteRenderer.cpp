void DWriteRenderer::SubpixelZoom()
{
    bool bgr = renderingParams_->GetPixelGeometry() == DWRITE_PIXEL_GEOMETRY_BGR;

    // Get the DIB selection selected into each IDWriteBitmapRenderTarget's memory DC.
    DIBSECTION srcDib;
    if (GetObject(GetCurrentObject(magnifierTarget_->GetMemoryDC(), OBJ_BITMAP), sizeof(srcDib), &srcDib) != sizeof(srcDib))
        return;

    DIBSECTION dstDib;
    if (GetObject(GetCurrentObject(renderTarget_->GetMemoryDC(), OBJ_BITMAP), sizeof(dstDib), &dstDib) != sizeof(dstDib))
        return;

    // Point to the pixels. Each DIB section is a 32-bit per pixel top-down DIB.
    int const srcWidth = srcDib.dsBm.bmWidth;
    int const srcHeight = srcDib.dsBm.bmHeight;
    UINT32 const* const srcBits = static_cast<UINT32*>(srcDib.dsBm.bmBits);

    int const dstWidth = dstDib.dsBm.bmWidth;
    int const dstHeight = dstDib.dsBm.bmHeight;
    UINT32* const dstBits = static_cast<UINT32*>(dstDib.dsBm.bmBits);

    // Number of target pixels per source pixel and source subpixel.
    int const scale = magnifier_.scale;
    int const subpixelScale = scale / 3;
    int const pixelGap = scale % 3;

    // Mask of colors for left, center, and right subpixels.
    UINT32 const maskL = bgr ? 0x0000FF : 0xFF0000;
    UINT32 const maskC = 0x00FF00;
    UINT32 const maskR = bgr ? 0xFF0000 : 0x0000FF;

    // Iterate over all the source scan lines.
    for (int y = 0; y < srcHeight; ++y)
    {
        UINT32 const* srcRow = srcBits + (y * srcWidth);

        // Determine the corresponding range of Y values in the destination bitmap.
        int minDstY = (y * scale) + magnifier_.magnifierPos.y;
        int limDstY = minDstY + scale;

        // Consrain the destination Y values to fit in the destination bitmap.
        if (minDstY < 0)
            minDstY = 0;

        if (limDstY > dstHeight)
            limDstY = dstHeight;

        // Are any of the destination scan lines visible?
        if (minDstY < limDstY)
        {
            UINT32* const firstDstRow = dstBits + (minDstY * dstWidth);

            int dstX = magnifier_.magnifierPos.x;

            // Iterate over all the pixels in the source scan line.
            for (int x = 0; x < srcWidth; ++x)
            {
                UINT32 const color = srcRow[x];

                // Fill in the destination pixels for the left, center,
                // and right color stripes.
                for (int i = 0; i < subpixelScale; ++i, ++dstX)
                {
                    if (dstX >= 0 && dstX < dstWidth)
                        firstDstRow[dstX] = color & maskL;
                }
                for (int i = 0; i < subpixelScale; ++i, ++dstX)
                {
                    if (dstX >= 0 && dstX < dstWidth)
                        firstDstRow[dstX] = color & maskC;
                }
                for (int i = 0; i < subpixelScale; ++i, ++dstX)
                {
                    if (dstX >= 0 && dstX < dstWidth)
                        firstDstRow[dstX] = color & maskR;
                }

                // If the scale is not a multiple if three, we'll have a black
                // gap between the pixels.
                for (int i = 0; i < pixelGap; ++i, ++dstX)
                {
                    if (dstX >= 0 && dstX < dstWidth)
                        firstDstRow[dstX] = 0;
                }
            }

            // Copy the destination row we just initialized to the remaining
            // destination rows for this scan line.
            UINT32* dstRow = firstDstRow + dstWidth;

            for (int y2 = minDstY + 1; y2 < limDstY; ++y2, dstRow += dstWidth)
            {
                memcpy(
                    dstRow + magnifier_.magnifierPos.x,
                    firstDstRow + magnifier_.magnifierPos.x,
                    (dstX - magnifier_.magnifierPos.x) * sizeof(UINT32)
                );
            }
        }
    }
}