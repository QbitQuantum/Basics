static void verify_region(HRGN hrgn, const RECT *rc)
{
    union
    {
        RGNDATA data;
        char buf[sizeof(RGNDATAHEADER) + sizeof(RECT)];
    } rgn;
    const RECT *rect;
    DWORD ret;

    ret = GetRegionData(hrgn, 0, NULL);
    if (IsRectEmpty(rc))
        ok(ret == sizeof(rgn.data.rdh), "expected sizeof(rdh), got %u\n", ret);
    else
        ok(ret == sizeof(rgn.data.rdh) + sizeof(RECT), "expected sizeof(rgn), got %u\n", ret);

    if (!ret) return;

    ret = GetRegionData(hrgn, sizeof(rgn), &rgn.data);
    if (IsRectEmpty(rc))
        ok(ret == sizeof(rgn.data.rdh), "expected sizeof(rdh), got %u\n", ret);
    else
        ok(ret == sizeof(rgn.data.rdh) + sizeof(RECT), "expected sizeof(rgn), got %u\n", ret);

    trace("size %u, type %u, count %u, rgn size %u, bound (%d,%d-%d,%d)\n",
          rgn.data.rdh.dwSize, rgn.data.rdh.iType,
          rgn.data.rdh.nCount, rgn.data.rdh.nRgnSize,
          rgn.data.rdh.rcBound.left, rgn.data.rdh.rcBound.top,
          rgn.data.rdh.rcBound.right, rgn.data.rdh.rcBound.bottom);
    if (rgn.data.rdh.nCount != 0)
    {
        rect = (const RECT *)rgn.data.Buffer;
        trace("rect (%d,%d-%d,%d)\n", rect->left, rect->top, rect->right, rect->bottom);
        ok(EqualRect(rect, rc), "rects don't match\n");
    }

    ok(rgn.data.rdh.dwSize == sizeof(rgn.data.rdh), "expected sizeof(rdh), got %u\n", rgn.data.rdh.dwSize);
    ok(rgn.data.rdh.iType == RDH_RECTANGLES, "expected RDH_RECTANGLES, got %u\n", rgn.data.rdh.iType);
    if (IsRectEmpty(rc))
    {
        ok(rgn.data.rdh.nCount == 0, "expected 0, got %u\n", rgn.data.rdh.nCount);
        ok(rgn.data.rdh.nRgnSize == 0 ||
           broken(rgn.data.rdh.nRgnSize == 168), /* NT4 */
           "expected 0, got %u\n", rgn.data.rdh.nRgnSize);
    }
    else
    {
        ok(rgn.data.rdh.nCount == 1, "expected 1, got %u\n", rgn.data.rdh.nCount);
        ok(rgn.data.rdh.nRgnSize == sizeof(RECT) ||
           broken(rgn.data.rdh.nRgnSize == 168), /* NT4 */
           "expected sizeof(RECT), got %u\n", rgn.data.rdh.nRgnSize);
    }
    ok(EqualRect(&rgn.data.rdh.rcBound, rc), "rects don't match\n");
}