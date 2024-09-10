bool plAVIWriterImp::Open(const char* fileName, plPipeline* pipeline)
{
#if HS_BUILD_FOR_WIN32
    // Already writing, fail
    if (fStreamHandle)
        return false;

    fStartTime = hsTimer::GetSysSeconds();

    // If we're running in real time, set to frame time
    fOldRealTime = hsTimer::IsRealTime();
    if (fOldRealTime)
    {
        hsTimer::SetRealTime(false);
        hsTimer::SetFrameTimeInc(1.f / kFramesPerSec);
    }

    // Open AVI file
    HRESULT err;
    err = AVIFileOpen(  &fFileHandle,           // returned file pointer
                        fileName,               // file name
                        OF_WRITE | OF_CREATE,   // mode to open file with
                        NULL);                  // use handler determined
    hsAssert(err == AVIERR_OK, "Error creating AVI file in plAVIWriter::Open");
    if (err != AVIERR_OK)
    {
        Close();
        return false;
    }

    AVISTREAMINFO streamInfo;
    IFillStreamInfo(&streamInfo, pipeline);

    // Create a video stream in the file
    err = AVIFileCreateStream(  fFileHandle,        // file pointer
                                &fStreamHandle,     // returned stream pointer
                                &streamInfo );      // stream header
    hsAssert(err == AVIERR_OK, "Error creating video stream in plAVIWriter::Open");
    if (err != AVIERR_OK)
    {
        Close();
        return false;
    }

    do
    {
        AVICOMPRESSOPTIONS opts;
        AVICOMPRESSOPTIONS FAR * aopts[1] = {&opts};
        memset(&opts, 0, sizeof(opts));

        BOOL bErr = AVISaveOptions(NULL, ICMF_CHOOSE_DATARATE, 1, &fStreamHandle, (LPAVICOMPRESSOPTIONS FAR*)&aopts);
        hsAssert(bErr, "Error saving stream options in plAVIWriter::Open");
        if (!bErr)
        {
            Close();
            return false;
        }

        err = AVIMakeCompressedStream(&fCompressedHandle, fStreamHandle, &opts, NULL);
        hsAssert(err == AVIERR_OK, "Error creating compressed stream in plAVIWriter::Open");
        if (err != AVIERR_OK)
        {
            Close();
            return false;
        }

        IFillBitmapInfo(&fBitmapInfo, pipeline);
        err = AVIStreamSetFormat(   fCompressedHandle, 0, 
                                    &fBitmapInfo,   // stream format
                                    fBitmapInfo.biSize);
    } while (err != AVIERR_OK &&
            hsMessageBox("Codec unavailable, try again?", "AVI Writer", hsMessageBoxYesNo) == hsMBoxYes);

    if (err != AVIERR_OK)
    {
        Close();
        return false;
    }
#endif

    plgDispatch::Dispatch()->RegisterForExactType(plRenderMsg::Index(), GetKey());

    return true;
}