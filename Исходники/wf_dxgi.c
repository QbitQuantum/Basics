int wf_dxgi_getInvalidRegion(RECT* invalid)
{
    UINT i;
    HRESULT status;
    UINT dirty;
    UINT BufSize;
    RECT* pRect;
    BYTE* DirtyRects;
    UINT DataBufferSize = 0;
    BYTE* DataBuffer = NULL;

    if (FrameInfo.AccumulatedFrames == 0)
    {
        return 1;
    }

    if (FrameInfo.TotalMetadataBufferSize)
    {

        if (FrameInfo.TotalMetadataBufferSize > DataBufferSize)
        {
            if (DataBuffer)
            {
                free(DataBuffer);
                DataBuffer = NULL;
            }

            DataBuffer = (BYTE*) malloc(FrameInfo.TotalMetadataBufferSize);

            if (!DataBuffer)
            {
                DataBufferSize = 0;
                _tprintf(_T("Failed to allocate memory for metadata\n"));
                exit(1);
            }

            DataBufferSize = FrameInfo.TotalMetadataBufferSize;
        }

        BufSize = FrameInfo.TotalMetadataBufferSize;

        status = gOutputDuplication->lpVtbl->GetFrameMoveRects(gOutputDuplication, BufSize, (DXGI_OUTDUPL_MOVE_RECT*) DataBuffer, &BufSize);

        if (FAILED(status))
        {
            _tprintf(_T("Failed to get frame move rects\n"));
            return 1;
        }

        DirtyRects = DataBuffer + BufSize;
        BufSize = FrameInfo.TotalMetadataBufferSize - BufSize;

        status = gOutputDuplication->lpVtbl->GetFrameDirtyRects(gOutputDuplication, BufSize, (RECT*) DirtyRects, &BufSize);

        if (FAILED(status))
        {
            _tprintf(_T("Failed to get frame dirty rects\n"));
            return 1;
        }
        dirty = BufSize / sizeof(RECT);

        pRect = (RECT*) DirtyRects;

        for(i = 0; i<dirty; ++i)
        {
            UnionRect(invalid, invalid, pRect);
            ++pRect;
        }
    }

    return 0;
}