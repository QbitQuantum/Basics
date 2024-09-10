static void test_mmio_buffer_pointer(void)
{
    char test_file[MAX_PATH];
    char buffer[5], data[16];
    MMIOINFO mmio;
    HMMIO hmmio;
    LONG size, pos;
    MMRESULT res;

    if (!create_test_file(test_file)) return;

    memset(&mmio, 0, sizeof(mmio));
    mmio.fccIOProc = FOURCC_DOS;
    mmio.pchBuffer = buffer;
    mmio.cchBuffer = sizeof(buffer);
    hmmio = mmioOpen(test_file, &mmio, MMIO_READ);
    ok(hmmio != NULL, "mmioOpen error %u\n", mmio.wErrorRet);
    if (hmmio == NULL) {
        DeleteFileA(test_file);
        return;
    }

    /* the buffer is empty */
    size = mmioRead(hmmio, data, 0);
    ok(size == 0, "expected 0, got %d\n", size);
    res = mmioGetInfo(hmmio, &mmio, 0);
    ok(res == MMSYSERR_NOERROR, "expected 0, got %d\n", res);
    ok(mmio.pchEndRead == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndRead);

    /* fill the buffer */
    size = mmioAdvance(hmmio, &mmio, MMIO_READ);
    ok(mmio.pchEndRead-mmio.pchBuffer == sizeof(buffer), "got %d\n", (int)(mmio.pchEndRead-mmio.pchBuffer));

    /* seeking to the same buffer chunk, the buffer is kept */
    size = sizeof(buffer)/2;
    pos = mmioSeek(hmmio, size, SEEK_SET);
    ok(pos == size, "failed to seek, expected %d, got %d\n", size, pos);
    res = mmioGetInfo(hmmio, &mmio, 0);
    ok(res == MMSYSERR_NOERROR, "expected 0, got %d\n", res);
    ok(mmio.lBufOffset == 0, "expected 0, got %d\n", mmio.lBufOffset);
    ok(mmio.pchNext-mmio.pchBuffer == size, "expected %d, got %d\n", size, (int)(mmio.pchNext-mmio.pchBuffer));
    ok(mmio.pchEndRead-mmio.pchBuffer == sizeof(buffer), "got %d\n", (int)(mmio.pchEndRead-mmio.pchBuffer));

    /* seeking to another buffer chunk, the buffer is empty */
    size = sizeof(buffer) * 3 + sizeof(buffer) / 2;
    pos = mmioSeek(hmmio, size, SEEK_SET);
    ok(pos == size, "failed to seek, got %d\n", pos);
    res = mmioGetInfo(hmmio, &mmio, 0);
    ok(res == MMSYSERR_NOERROR, "expected 0, got %d\n", res);
    ok(mmio.lBufOffset == size, "expected %d, got %d\n", size, mmio.lBufOffset);
    ok(mmio.pchNext == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchNext);
    ok(mmio.pchEndRead == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndRead);

    /* reading a lot (as sizeof(data) > mmio.cchBuffer), the buffer is empty */
    size = mmioRead(hmmio, data, sizeof(data));
    ok(size == sizeof(data), "failed to read, got %d\n", size);
    res = mmioGetInfo(hmmio, &mmio, 0);
    ok(res == MMSYSERR_NOERROR, "expected 0, got %d\n", res);
    ok(mmio.lBufOffset == pos+size, "expected %d, got %d\n", pos+size, mmio.lBufOffset);
    ok(mmio.pchNext == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchNext);
    ok(mmio.pchEndRead == mmio.pchBuffer, "expected %p, got %p\n", mmio.pchBuffer, mmio.pchEndRead);

    mmioClose(hmmio, 0);
    DeleteFileA(test_file);
}