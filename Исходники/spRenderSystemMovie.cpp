void Movie::close()
{
    if (DataPointer_)
    {
        /* Delete each movie object data */
        DeleteObject(mcrAVIData->hBitmap);
        DrawDibClose(mcrAVIData->hDrawDIB);
        
        AVIStreamGetFrameClose(mcrAVIData->pGetFrame);
        AVIStreamRelease(mcrAVIData->pVideoStream);
        AVIFileExit();
        
        /* Delete the movie data */
        delete mcrAVIData;
    }
}