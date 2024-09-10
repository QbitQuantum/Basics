PRBool
nsThebesImage::ShouldUseImageSurfaces()
{
#ifdef XP_WIN
    static const DWORD kGDIObjectsHighWaterMark = 7000;

    // at 7000 GDI objects, stop allocating normal images to make sure
    // we never hit the 10k hard limit.
    // GetCurrentProcess() just returns (HANDLE)-1, it's inlined afaik
    DWORD count = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);
    if (count == 0 ||
        count > kGDIObjectsHighWaterMark)
    {
        // either something's broken (count == 0),
        // or we hit our high water mark; disable
        // image allocations for a bit.
        return PR_TRUE;
    }
#endif

    return PR_FALSE;
}