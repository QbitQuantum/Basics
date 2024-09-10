static void Resize(const Capture * capBox, LPBYTE output, const BYTE *input)
{
    /* the whole image needs to be reversed,
       because the dibs are messed up in windows */
    if (!capBox->swresize)
    {
        int depth = capBox->bitDepth / 8;
        int inoffset = 0, outoffset = capBox->height * capBox->width * depth;
        int ow = capBox->width * depth;
        while (outoffset > 0)
        {
            int x;
            outoffset -= ow;
            for (x = 0; x < ow; x++)
                output[outoffset + x] = input[inoffset + x];
            inoffset += ow;
        }
    }
    else
    {
        HDC dc_s, dc_d;
        HBITMAP bmp_s, bmp_d;
        int depth = capBox->bitDepth / 8;
        int inoffset = 0, outoffset = (capBox->outputheight) * capBox->outputwidth * depth;
        int ow = capBox->outputwidth * depth;
        LPBYTE myarray;

        /* FIXME: Improve software resizing: add error checks and optimize */

        myarray = CoTaskMemAlloc(capBox->outputwidth * capBox->outputheight * depth);
        dc_s = CreateCompatibleDC(NULL);
        dc_d = CreateCompatibleDC(NULL);
        bmp_s = CreateBitmap(capBox->width, capBox->height, 1, capBox->bitDepth, input);
        bmp_d = CreateBitmap(capBox->outputwidth, capBox->outputheight, 1, capBox->bitDepth, NULL);
        SelectObject(dc_s, bmp_s);
        SelectObject(dc_d, bmp_d);
        StretchBlt(dc_d, 0, 0, capBox->outputwidth, capBox->outputheight,
                   dc_s, 0, 0, capBox->width, capBox->height, SRCCOPY);
        GetBitmapBits(bmp_d, capBox->outputwidth * capBox->outputheight * depth, myarray);
        while (outoffset > 0)
        {
            int i;

            outoffset -= ow;
            for (i = 0; i < ow; i++)
                output[outoffset + i] = myarray[inoffset + i];
            inoffset += ow;
        }
        CoTaskMemFree(myarray);
        DeleteObject(dc_s);
        DeleteObject(dc_d);
        DeleteObject(bmp_s);
        DeleteObject(bmp_d);
    }
}