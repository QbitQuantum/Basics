void SharedBitmap::drawPattern(HDC hdc, const AffineTransform& transform, const FloatRect& tileRectIn, const AffineTransform& patternTransform,
                        const FloatPoint& phase, ColorSpace styleColorSpace, CompositeOperator op, const FloatRect& destRect, const IntSize& origSourceSize)
{
    if (!m_pixels)
        return;

    if (tileRectIn.width() <= 0 || tileRectIn.height() <= 0)
        return;

    bool useAlpha = op == CompositeSourceOver && hasAlpha() && is32bit();

    int bmpWidth = width();
    int bmpHeight = height();

    FloatRect tileRect(tileRectIn);
    if (bmpWidth != origSourceSize.width()) {
        double rate = static_cast<double>(bmpWidth) / origSourceSize.width();
        double temp = tileRect.width() * rate;
        tileRect.setX(tileRect.x() * rate);
        tileRect.setWidth(temp);
        temp = tileRect.height() * rate;
        tileRect.setY(tileRect.y() * rate);
        tileRect.setHeight(temp);
    }

    OwnPtr<HBITMAP> clippedBmp;

    if (tileRect.x() || tileRect.y() || tileRect.width() != bmpWidth || tileRect.height() != bmpHeight) {
        BitmapInfo patternBmpInfo;
        void* patternPixels;
        clippedBmp = clipBitmap(IntRect(tileRect), useAlpha, patternBmpInfo, patternPixels);
        if (!clippedBmp)
            return;

        bmpWidth = tileRect.width();
        bmpHeight = tileRect.height();
    }

    AffineTransform tf = patternTransform * transform;

    FloatRect trRect = tf.mapRect(destRect);

    RECT clipBox;
    int clipType = GetClipBox(hdc, &clipBox);
    if (clipType == SIMPLEREGION)
        trRect.intersect(FloatRect(clipBox.left, clipBox.top, clipBox.right - clipBox.left, clipBox.bottom - clipBox.top));
    else if (clipType == COMPLEXREGION) {
        OwnPtr<HRGN> clipRgn = adoptPtr(CreateRectRgn(0, 0, 0, 0));
        if (GetClipRgn(hdc, clipRgn.get()) > 0) {
            DWORD regionDataSize = GetRegionData(clipRgn.get(), sizeof(RGNDATA), 0);
            if (regionDataSize) {
                Vector<RGNDATA> regionData(regionDataSize);
                GetRegionData(clipRgn.get(), regionDataSize, regionData.data());
                RECT* rect = reinterpret_cast<RECT*>(regionData[0].Buffer);
                for (DWORD i = 0; i < regionData[0].rdh.nCount; ++i, ++rect)
                    trRect.intersect(FloatRect(rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top));
            }
        }
    }

    if (trRect.width() <= 0 || trRect.height() <= 0)
        return;

    trRect.inflate(1);
    IntRect visibleDstRect = enclosingIntRect(tf.inverse().mapRect(trRect));
    visibleDstRect.intersect(IntRect(destRect));

    if (visibleDstRect.width() <= 0 || visibleDstRect.height() <= 0)
        return;

    trRect = tf.mapRect(visibleDstRect);
    RECT dstRectWin = {
        stableRound(trRect.x()),
        stableRound(trRect.y()),
        stableRound(trRect.maxX()),
        stableRound(trRect.maxY()),
    };
    if (dstRectWin.right <= dstRectWin.left || dstRectWin.bottom <= dstRectWin.top)
        return;

    SIZE bmpSize = { bmpWidth, bmpHeight };

    // Relative to destination, in bitmap pixels
    POINT phaseWin = { stableRound(visibleDstRect.x() - phase.x()), stableRound(visibleDstRect.y() - phase.y()) };
    phaseWin.x = normalizePhase(phaseWin.x, bmpSize.cx);
    phaseWin.y = normalizePhase(phaseWin.y, bmpSize.cy);

    RECT srcRectWin = {
        0,
        0,
        stableRound(visibleDstRect.maxX()) - stableRound(visibleDstRect.x()),
        stableRound(visibleDstRect.maxY()) - stableRound(visibleDstRect.y())
    };
    if (srcRectWin.right <= 0 || srcRectWin.bottom <= 0)
        return;

    BitmapInfo bmpInfo = BitmapInfo::createBottomUp(IntSize(srcRectWin.right, srcRectWin.bottom), useAlpha ? BitmapInfo::BitCount32 : BitmapInfo::BitCount16);
    void* pixels;
    OwnPtr<HBITMAP> hbmpTemp = adoptPtr(CreateDIBSection(0, &bmpInfo, DIB_RGB_COLORS, &pixels, 0, 0));

    if (!hbmpTemp)
        return;

    OwnPtr<HDC> hmemdc = adoptPtr(CreateCompatibleDC(hdc));
    HGDIOBJ oldBmp = SelectObject(hmemdc.get(), hbmpTemp.get());
    if (clippedBmp)
        drawPatternSimple(hmemdc.get(), srcRectWin, clippedBmp.get(), phaseWin);
    else if ((op != CompositeSourceOver || canUseDIBits()) && srcRectWin.right <= bmpSize.cx * 2 && srcRectWin.bottom <= bmpSize.cy * 2)
        drawPatternSimple(hmemdc.get(), srcRectWin, this, bmpSize, phaseWin);
    else if (ensureHandle())
        drawPatternSimple(hmemdc.get(), srcRectWin, getHandle(), phaseWin);
    else {
        void* pixels;
        BitmapInfo bmpInfo;
        OwnPtr<HBITMAP> hbmp = createHandle(&pixels, &bmpInfo, -1, false);
        if (hbmp)
            drawPatternSimple(hmemdc.get(), srcRectWin, hbmp.get(), phaseWin);
        else {
            SelectObject(hmemdc.get(), oldBmp);
            return;
        }
    }

    if (useAlpha && hasAlphaBlendSupport()) {
        static const BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
        bool success = alphaBlendIfSupported(hdc, dstRectWin.left, dstRectWin.top, dstRectWin.right - dstRectWin.left, dstRectWin.bottom - dstRectWin.top,
            hmemdc.get(), 0, 0, srcRectWin.right, srcRectWin.bottom, blend);
        ASSERT_UNUSED(success, success);
    } else if (useAlpha && !hasAlphaBlendSupport() || op == CompositeSourceOver && usesTransparentColor()) {
        TransparentBlt(hdc, dstRectWin.left, dstRectWin.top, dstRectWin.right - dstRectWin.left,
            dstRectWin.bottom - dstRectWin.top, hmemdc.get(), 0, 0, srcRectWin.right, srcRectWin.bottom, transparentColor());
    } else {
        DWORD bmpOp = op == CompositeCopy ? SRCCOPY
                    : op == CompositeSourceOver ? SRCCOPY
                    : op == CompositeXOR ? PATINVERT
                    : op == CompositeClear ? WHITENESS
                    : SRCCOPY; // FIXEME: other types?

        StretchDIBits(hdc, dstRectWin.left, dstRectWin.top, dstRectWin.right - dstRectWin.left,
            dstRectWin.bottom - dstRectWin.top, 0, 0, srcRectWin.right, srcRectWin.bottom,
            pixels, &bmpInfo, DIB_RGB_COLORS, bmpOp);
    }
    SelectObject(hmemdc.get(), oldBmp);
}