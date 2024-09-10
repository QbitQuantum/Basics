static void getDirtyRects(HWND window, Vector<CGRect>& outRects)
{
    ASSERT_ARG(outRects, outRects.isEmpty());

    RECT clientRect;
    if (!GetClientRect(window, &clientRect))
        return;

    HRGN region = CreateRectRgn(0, 0, 0, 0);
    int regionType = GetUpdateRgn(window, region, false);
    if (regionType != COMPLEXREGION) {
        RECT dirtyRect;
        if (GetUpdateRect(window, &dirtyRect, false))
            outRects.append(winRectToCGRect(dirtyRect, clientRect));
        return;
    }

    DWORD dataSize = GetRegionData(region, 0, 0);
    OwnArrayPtr<unsigned char> regionDataBuffer(new unsigned char[dataSize]);
    RGNDATA* regionData = reinterpret_cast<RGNDATA*>(regionDataBuffer.get());
    if (!GetRegionData(region, dataSize, regionData))
        return;

    outRects.resize(regionData->rdh.nCount);

    RECT* rect = reinterpret_cast<RECT*>(regionData->Buffer);
    for (size_t i = 0; i < outRects.size(); ++i, ++rect)
        outRects[i] = winRectToCGRect(*rect, clientRect);

    DeleteObject(region);
}