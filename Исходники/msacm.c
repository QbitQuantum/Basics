static void test_prepareheader(void)
{
    HACMSTREAM has;
    ADPCMWAVEFORMAT *src;
    WAVEFORMATEX dst;
    MMRESULT mr;
    ACMSTREAMHEADER hdr;
    BYTE buf[sizeof(WAVEFORMATEX) + 32], pcm[2048], input[512];
    ADPCMCOEFSET *coef;

    src = (ADPCMWAVEFORMAT*)buf;
    coef = src->aCoef;
    src->wfx.cbSize = 32;
    src->wfx.wFormatTag = WAVE_FORMAT_ADPCM;
    src->wfx.nSamplesPerSec = 22050;
    src->wfx.wBitsPerSample = 4;
    src->wfx.nChannels = 1;
    src->wfx.nBlockAlign = 512;
    src->wfx.nAvgBytesPerSec = 11025;
    src->wSamplesPerBlock = 0x3f4;
    src->wNumCoef = 7;
    coef[0].iCoef1 = 0x0100;
    coef[0].iCoef2 = 0x0000;
    coef[1].iCoef1 = 0x0200;
    coef[1].iCoef2 = 0xff00;
    coef[2].iCoef1 = 0x0000;
    coef[2].iCoef2 = 0x0000;
    coef[3].iCoef1 = 0x00c0;
    coef[3].iCoef2 = 0x0040;
    coef[4].iCoef1 = 0x00f0;
    coef[4].iCoef2 = 0x0000;
    coef[5].iCoef1 = 0x01cc;
    coef[5].iCoef2 = 0xff30;
    coef[6].iCoef1 = 0x0188;
    coef[6].iCoef2 = 0xff18;

    dst.cbSize = 0;
    dst.wFormatTag = WAVE_FORMAT_PCM;
    dst.nSamplesPerSec = 22050;
    dst.wBitsPerSample = 8;
    dst.nChannels = 1;
    dst.nBlockAlign = dst.wBitsPerSample * dst.nChannels / 8;
    dst.nAvgBytesPerSec = dst.nSamplesPerSec * dst.nBlockAlign;

    mr = acmStreamOpen(&has, NULL, (WAVEFORMATEX*)src, &dst, NULL, 0, 0, 0);
    ok(mr == MMSYSERR_NOERROR, "open failed: 0x%x\n", mr);

    memset(input, 0, sizeof(input));
    memset(&hdr, 0, sizeof(hdr));
    hdr.cbStruct = sizeof(hdr);
    hdr.pbSrc = input;
    hdr.cbSrcLength = sizeof(input);
    hdr.pbDst = pcm;
    hdr.cbDstLength = sizeof(pcm);

    mr = acmStreamPrepareHeader(has, &hdr, 0);
    ok(mr == MMSYSERR_NOERROR, "prepare failed: 0x%x\n", mr);
    ok(hdr.fdwStatus == ACMSTREAMHEADER_STATUSF_PREPARED, "header wasn't prepared: 0x%x\n", hdr.fdwStatus);

    mr = acmStreamUnprepareHeader(has, &hdr, 0);
    ok(mr == MMSYSERR_NOERROR, "unprepare failed: 0x%x\n", mr);
    ok(hdr.fdwStatus == 0, "header wasn't unprepared: 0x%x\n", hdr.fdwStatus);

    memset(&hdr, 0, sizeof(hdr));
    hdr.cbStruct = sizeof(hdr);
    hdr.pbSrc = input;
    hdr.cbSrcLength = sizeof(input);
    hdr.pbDst = pcm;
    hdr.cbDstLength = sizeof(pcm);
    hdr.fdwStatus = ACMSTREAMHEADER_STATUSF_DONE;

    mr = acmStreamPrepareHeader(has, &hdr, 0);
    ok(mr == MMSYSERR_NOERROR, "prepare failed: 0x%x\n", mr);
    ok(hdr.fdwStatus == (ACMSTREAMHEADER_STATUSF_PREPARED | ACMSTREAMHEADER_STATUSF_DONE), "header wasn't prepared: 0x%x\n", hdr.fdwStatus);

    hdr.cbSrcLengthUsed = 12345;
    hdr.cbDstLengthUsed = 12345;
    hdr.fdwStatus &= ~ACMSTREAMHEADER_STATUSF_DONE;
    mr = acmStreamConvert(has, &hdr, ACM_STREAMCONVERTF_BLOCKALIGN);
    ok(mr == MMSYSERR_NOERROR, "convert failed: 0x%x\n", mr);
    ok(hdr.fdwStatus & ACMSTREAMHEADER_STATUSF_DONE, "conversion was not done: 0x%x\n", hdr.fdwStatus);
    ok(hdr.cbSrcLengthUsed == hdr.cbSrcLength, "expected %d, got %d\n", hdr.cbSrcLength, hdr.cbSrcLengthUsed);
    todo_wine
    ok(hdr.cbDstLengthUsed == 1010, "expected 1010, got %d\n", hdr.cbDstLengthUsed);

    mr = acmStreamUnprepareHeader(has, &hdr, 0);
    ok(mr == MMSYSERR_NOERROR, "unprepare failed: 0x%x\n", mr);
    ok(hdr.fdwStatus == ACMSTREAMHEADER_STATUSF_DONE, "header wasn't unprepared: 0x%x\n", hdr.fdwStatus);

    /* The 2 next tests are related to Lost Horizon (bug 24723) */
    memset(&hdr, 0, sizeof(hdr));
    hdr.cbStruct = sizeof(hdr);
    hdr.pbSrc = input;
    hdr.cbSrcLength = sizeof(input);
    hdr.pbDst = pcm;
    hdr.cbDstLength = -4;

    mr = acmStreamPrepareHeader(has, &hdr, 0);
    if (sizeof(void *) == 4) /* 64 bit fails on this test */
    {
        ok(mr == MMSYSERR_NOERROR, "prepare failed: 0x%x\n", mr);
        ok(hdr.fdwStatus == ACMSTREAMHEADER_STATUSF_PREPARED, "header wasn't prepared: 0x%x\n", hdr.fdwStatus);

        hdr.cbSrcLengthUsed = 12345;
        hdr.cbDstLengthUsed = 12345;
        hdr.fdwStatus &= ~ACMSTREAMHEADER_STATUSF_DONE;
        mr = acmStreamConvert(has, &hdr, ACM_STREAMCONVERTF_BLOCKALIGN);
        ok(mr == MMSYSERR_NOERROR, "convert failed: 0x%x\n", mr);
        ok(hdr.fdwStatus & ACMSTREAMHEADER_STATUSF_DONE, "conversion was not done: 0x%x\n", hdr.fdwStatus);
        ok(hdr.cbSrcLengthUsed == hdr.cbSrcLength, "expected %d, got %d\n", hdr.cbSrcLength, hdr.cbSrcLengthUsed);
        todo_wine
        ok(hdr.cbDstLengthUsed == 1010, "expected 1010, got %d\n", hdr.cbDstLengthUsed);

        mr = acmStreamUnprepareHeader(has, &hdr, 0);
        ok(mr == MMSYSERR_NOERROR, "unprepare failed: 0x%x\n", mr);
        ok(hdr.fdwStatus == ACMSTREAMHEADER_STATUSF_DONE, "header wasn't unprepared: 0x%x\n", hdr.fdwStatus);
    }
    else
        ok(mr == MMSYSERR_INVALPARAM, "expected 11, got %d\n", mr);

    memset(&hdr, 0, sizeof(hdr));
    hdr.cbStruct = sizeof(hdr);
    hdr.pbSrc = input;
    hdr.cbSrcLength = 24;
    hdr.pbDst = pcm;
    hdr.cbDstLength = -4;
    mr = acmStreamPrepareHeader(has, &hdr, 0);
    todo_wine {
        ok(mr == ACMERR_NOTPOSSIBLE, "expected 0x200, got 0x%x\n", mr);
        ok(hdr.fdwStatus == 0, "expected 0, got 0x%x\n", hdr.fdwStatus);

        hdr.cbSrcLengthUsed = 12345;
        hdr.cbDstLengthUsed = 12345;
        mr = acmStreamConvert(has, &hdr, ACM_STREAMCONVERTF_BLOCKALIGN);
        ok(mr == ACMERR_UNPREPARED, "expected 0x202, got 0x%x\n", mr);
        ok(hdr.cbSrcLengthUsed == 12345, "expected 12345, got %d\n", hdr.cbSrcLengthUsed);
        ok(hdr.cbDstLengthUsed == 12345, "expected 12345, got %d\n", hdr.cbDstLengthUsed);

        mr = acmStreamUnprepareHeader(has, &hdr, 0);
        ok(mr == ACMERR_UNPREPARED, "expected 0x202, got 0x%x\n", mr);
    }
    /* Less output space than required */
    memset(&hdr, 0, sizeof(hdr));
    hdr.cbStruct = sizeof(hdr);
    hdr.pbSrc = input;
    hdr.cbSrcLength = sizeof(input);
    hdr.pbDst = pcm;
    hdr.cbDstLength = 32;

    mr = acmStreamPrepareHeader(has, &hdr, 0);
    ok(mr == MMSYSERR_NOERROR, "prepare failed: 0x%x\n", mr);
    ok(hdr.fdwStatus == ACMSTREAMHEADER_STATUSF_PREPARED, "header wasn't prepared: 0x%x\n", hdr.fdwStatus);

    hdr.cbSrcLengthUsed = 12345;
    hdr.cbDstLengthUsed = 12345;
    hdr.fdwStatus &= ~ACMSTREAMHEADER_STATUSF_DONE;
    mr = acmStreamConvert(has, &hdr, ACM_STREAMCONVERTF_BLOCKALIGN);
    ok(mr == MMSYSERR_NOERROR, "convert failed: 0x%x\n", mr);
    ok(hdr.fdwStatus & ACMSTREAMHEADER_STATUSF_DONE, "conversion was not done: 0x%x\n", hdr.fdwStatus);
    todo_wine
    ok(hdr.cbSrcLengthUsed == hdr.cbSrcLength, "expected %d, got %d\n", hdr.cbSrcLength, hdr.cbSrcLengthUsed);
    todo_wine
    ok(hdr.cbDstLengthUsed == hdr.cbDstLength, "expected %d, got %d\n", hdr.cbDstLength, hdr.cbDstLengthUsed);

    mr = acmStreamUnprepareHeader(has, &hdr, 0);
    ok(mr == MMSYSERR_NOERROR, "unprepare failed: 0x%x\n", mr);
    ok(hdr.fdwStatus == ACMSTREAMHEADER_STATUSF_DONE, "header wasn't unprepared: 0x%x\n", hdr.fdwStatus);

    mr = acmStreamClose(has, 0);
    ok(mr == MMSYSERR_NOERROR, "close failed: 0x%x\n", mr);
}