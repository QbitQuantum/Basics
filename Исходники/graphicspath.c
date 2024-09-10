static void test_isvisible(void)
{
    GpPath *path;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC(0);
    BOOL result;
    GpStatus status;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);

    /* NULL */
    status = GdipIsVisiblePathPoint(NULL, 0.0, 0.0, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, graphics, NULL);
    expect(InvalidParameter, status);

    /* empty path */
    result = TRUE;
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, NULL, &result);
    expect(Ok, status);
    expect(FALSE, result);
    /* rect */
    status = GdipAddPathRectangle(path, 0.0, 0.0, 10.0, 10.0);
    expect(Ok, status);
    result = FALSE;
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, NULL, &result);
    expect(Ok, status);
    expect(TRUE, result);
    result = TRUE;
    status = GdipIsVisiblePathPoint(path, 11.0, 11.0, NULL, &result);
    expect(Ok, status);
    expect(FALSE, result);
    /* not affected by clipping */
    status = GdipSetClipRect(graphics, 5.0, 5.0, 5.0, 5.0, CombineModeReplace);
    expect(Ok, status);
    result = FALSE;
    status = GdipIsVisiblePathPoint(path, 0.0, 0.0, graphics, &result);
    expect(Ok, status);
    expect(TRUE, result);

    GdipDeletePath(path);
    GdipDeleteGraphics(graphics);
    ReleaseDC(0, hdc);
}