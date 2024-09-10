static void test_ICSeqCompress(void)
{
    /* The purpose of this test is to validate sequential frame compressing
     * functions. The MRLE codec will be used because Wine supports it and
     * it is present in any Windows.
     */
    HIC h;
    DWORD err, vidc = mmioFOURCC('v','i','d','c'), mrle = mmioFOURCC('m', 'r', 'l', 'e');
    DWORD i;
    LONG frame_len;
    BOOL key_frame, ret;
    char *frame;
    COMPVARS pc;
    struct { BITMAPINFOHEADER header; RGBQUAD map[256]; }
    input_header = { {sizeof(BITMAPINFOHEADER), 32, 1, 1, 8, 0, 32*8, 0, 0, 256, 256},
                     {{255,0,0}, {0,255,0}, {0,0,255}, {255,255,255}}};
    PBITMAPINFO bitmap = (PBITMAPINFO) &input_header;
    static BYTE input[32] = {1,2,3,3,3,3,2,3,1};
    static const BYTE output_kf[] = {1,1,1,2,4,3,0,3,2,3,1,0,23,0,0,0,0,1}, /* key frame*/
                      output_nkf[] = {0,0,0,1}; /* non key frame */

    h = ICOpen(vidc, mrle, ICMODE_COMPRESS);
    ok(h != NULL, "Expected non-NULL\n");

    pc.cbSize = sizeof(pc);
    pc.dwFlags    = ICMF_COMPVARS_VALID;
    pc.fccType    = vidc;
    pc.fccHandler = mrle;
    pc.hic        = h;
    pc.lpbiIn     = NULL;
    pc.lpbiOut    = NULL;
    pc.lpBitsOut  = pc.lpBitsPrev = pc.lpState = NULL;
    pc.lQ         = ICQUALITY_DEFAULT;
    pc.lKey       = 1;
    pc.lDataRate  = 300;
    pc.lpState    = NULL;
    pc.cbState    = 0;

    ret = ICSeqCompressFrameStart(&pc, bitmap);
    ok(ret == TRUE, "Expected TRUE\n");
    /* Check that reserved pointers were allocated */
    ok(pc.lpbiIn != NULL, "Expected non-NULL\n");
    ok(pc.lpbiOut != NULL, "Expected non-NULL\n");

    for(i = 0; i < 9; i++)
    {
        frame_len = 0;
        frame = ICSeqCompressFrame(&pc, 0, input, &key_frame, &frame_len);
        ok(frame != NULL, "Frame[%d]: Expected non-NULL\n", i);
        if (frame_len == sizeof(output_nkf))
            ok(!memcmp(output_nkf, frame, frame_len), "Frame[%d]: Contents do not match\n", i);
        else if (frame_len == sizeof(output_kf))
            ok(!memcmp(output_kf, frame, frame_len), "Frame[%d]: Contents do not match\n", i);
        else
            ok(0, "Unknown frame size of %d byten\n", frame_len);
    }

    ICSeqCompressFrameEnd(&pc);
    ICCompressorFree(&pc);
    /* ICCompressorFree already closed the HIC */
    err = ICClose(h);
    ok(err == ICERR_BADHANDLE, "Expected -8, got %d\n", err);
}