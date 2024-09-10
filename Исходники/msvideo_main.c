/***********************************************************************
 *		ICGetDisplayFormat			[MSVFW32.@]
 */
HIC VFWAPI ICGetDisplayFormat(HIC hic, BITMAPINFOHEADER *in, BITMAPINFOHEADER *out,
                              int depth, int width, int height)
{
    HIC tmphic = hic;

    TRACE("(%p, %p, %p, %d, %d, %d)\n", hic, in, out, depth, width, height);

    if (!tmphic)
    {
        tmphic = ICLocate(ICTYPE_VIDEO, 0, in, NULL, ICMODE_DECOMPRESS);
        if (!tmphic)
            return NULL;
    }

    if (ICDecompressQuery(tmphic, in, NULL))
        goto err;

    if (width <= 0 || height <= 0)
    {
        width = in->biWidth;
        height = in->biHeight;
    }

    if (!depth)
        depth = 32;

    *out = *in;
    out->biSize = sizeof(*out);
    out->biWidth = width;
    out->biHeight = height;
    out->biCompression = BI_RGB;
    out->biSizeImage = get_size_image(width, height, depth);

    /* first try the given depth */
    out->biBitCount = depth;
    out->biSizeImage = get_size_image(width, height, out->biBitCount);
    if (!ICDecompressQuery(tmphic, in, out))
    {
        if (depth == 8)
            ICDecompressGetPalette(tmphic, in, out);
        return tmphic;
    }

    /* then try 16, both with BI_RGB and BI_BITFIELDS */
    if (depth <= 16)
    {
        out->biBitCount = 16;
        out->biSizeImage = get_size_image(width, height, out->biBitCount);
        if (!ICDecompressQuery(tmphic, in, out))
            return tmphic;

        out->biCompression = BI_BITFIELDS;
        if (!ICDecompressQuery(tmphic, in, out))
            return tmphic;
        out->biCompression = BI_RGB;
    }

    /* then try 24 */
    if (depth <= 24)
    {
        out->biBitCount = 24;
        out->biSizeImage = get_size_image(width, height, out->biBitCount);
        if (!ICDecompressQuery(tmphic, in, out))
            return tmphic;
    }

    /* then try 32 */
    if (depth <= 32)
    {
        out->biBitCount = 32;
        out->biSizeImage = get_size_image(width, height, out->biBitCount);
        if (!ICDecompressQuery(tmphic, in, out))
            return tmphic;
    }

    /* as a last resort, try 32 bpp with the original width and height */
    out->biWidth = in->biWidth;
    out->biHeight = in->biHeight;
    out->biBitCount = 32;
    out->biSizeImage = get_size_image(out->biWidth, out->biHeight, out->biBitCount);
    if (!ICDecompressQuery(tmphic, in, out))
        return tmphic;

    /* finally, ask the compressor for its default output format */
    if (!ICSendMessage(tmphic, ICM_DECOMPRESS_GET_FORMAT, (DWORD_PTR)in, (DWORD_PTR)out))
        return tmphic;

err:
    if (hic != tmphic)
        ICClose(tmphic);

    return NULL;
}