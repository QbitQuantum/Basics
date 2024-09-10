static BOOL SaveIconResAsPNG(const BITMAPINFO *pIcon, const char *png_filename, LPCWSTR commentW)
{
    static const char comment_key[] = "Created from";
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_text comment;
    int nXORWidthBytes, nANDWidthBytes, color_type = 0, i, j;
    BYTE *row, *copy = NULL;
    const BYTE *pXOR, *pAND = NULL;
    int nWidth  = pIcon->bmiHeader.biWidth;
    int nHeight = pIcon->bmiHeader.biHeight;
    int nBpp    = pIcon->bmiHeader.biBitCount;

    switch (nBpp)
    {
    case 32:
        color_type |= PNG_COLOR_MASK_ALPHA;
        /* fall through */
    case 24:
        color_type |= PNG_COLOR_MASK_COLOR;
        break;
    default:
        return FALSE;
    }

    if (!libpng_handle && !load_libpng())
    {
        WINE_WARN("Unable to load libpng\n");
        return FALSE;
    }

    if (!(fp = fopen(png_filename, "w")))
    {
        WINE_ERR("unable to open '%s' for writing: %s\n", png_filename, strerror(errno));
        return FALSE;
    }

    nXORWidthBytes = 4 * ((nWidth * nBpp + 31) / 32);
    nANDWidthBytes = 4 * ((nWidth + 31 ) / 32);
    pXOR = (const BYTE*) pIcon + sizeof(BITMAPINFOHEADER) + pIcon->bmiHeader.biClrUsed * sizeof(RGBQUAD);
    if (nHeight > nWidth)
    {
        nHeight /= 2;
        pAND = pXOR + nHeight * nXORWidthBytes;
    }

    /* Apply mask if present */
    if (pAND)
    {
        RGBQUAD bgColor;

        /* copy bytes before modifying them */
        copy = HeapAlloc( GetProcessHeap(), 0, nHeight * nXORWidthBytes );
        memcpy( copy, pXOR, nHeight * nXORWidthBytes );
        pXOR = copy;

        /* image and mask are upside down reversed */
        row = copy + (nHeight - 1) * nXORWidthBytes;

        /* top left corner */
        bgColor.rgbRed   = row[0];
        bgColor.rgbGreen = row[1];
        bgColor.rgbBlue  = row[2];
        bgColor.rgbReserved = 0;

        for (i = 0; i < nHeight; i++, row -= nXORWidthBytes)
            for (j = 0; j < nWidth; j++, row += nBpp >> 3)
                if (MASK(j, i))
                {
                    RGBQUAD *pixel = (RGBQUAD *)row;
                    pixel->rgbBlue  = bgColor.rgbBlue;
                    pixel->rgbGreen = bgColor.rgbGreen;
                    pixel->rgbRed   = bgColor.rgbRed;
                    if (nBpp == 32)
                        pixel->rgbReserved = bgColor.rgbReserved;
                }
    }

    comment.text = NULL;

    if (!(png_ptr = ppng_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)) ||
        !(info_ptr = ppng_create_info_struct(png_ptr)))
        goto error;

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        /* All future errors jump here */
        WINE_ERR("png error\n");
        goto error;
    }

    ppng_init_io(png_ptr, fp);
    ppng_set_IHDR(png_ptr, info_ptr, nWidth, nHeight, 8,
                  color_type,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    /* Set comment */
    comment.compression = PNG_TEXT_COMPRESSION_NONE;
    comment.key = (png_charp)comment_key;
    i = WideCharToMultiByte(CP_UNIXCP, 0, commentW, -1, NULL, 0, NULL, NULL);
    comment.text = HeapAlloc(GetProcessHeap(), 0, i);
    WideCharToMultiByte(CP_UNIXCP, 0, commentW, -1, comment.text, i, NULL, NULL);
    comment.text_length = i - 1;
    ppng_set_text(png_ptr, info_ptr, &comment, 1);


    ppng_write_info(png_ptr, info_ptr);
    ppng_set_bgr(png_ptr);
    for (i = nHeight - 1; i >= 0 ; i--)
        ppng_write_row(png_ptr, (png_bytep)pXOR + nXORWidthBytes * i);
    ppng_write_end(png_ptr, info_ptr);

    ppng_destroy_write_struct(&png_ptr, &info_ptr);
    if (png_ptr) ppng_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    HeapFree(GetProcessHeap(), 0, copy);
    HeapFree(GetProcessHeap(), 0, comment.text);
    return TRUE;

 error:
    if (png_ptr) ppng_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    unlink(png_filename);
    HeapFree(GetProcessHeap(), 0, copy);
    HeapFree(GetProcessHeap(), 0, comment.text);
    return FALSE;
}