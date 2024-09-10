void Matroska_MetaHandler::WriteTempFile(XMP_IO* tempRef)
{
    XMP_Assert(needsUpdate);

    XMP_IO* originalRef = parent->ioRef;
    
    bool localProgressTracking(false);
    XMP_ProgressTracker* progressTracker = parent->progressTracker;
    if (progressTracker)
    {
        float xmpSize = static_cast<float>(xmpPacket.size());
        if (progressTracker->WorkInProgress())
        {
            progressTracker->AddTotalWork(xmpSize);
        }
        else
        {
            localProgressTracking = true;
            progressTracker->BeginWork(xmpSize);
        }
    }

    XMP_Assert(tempRef);
    XMP_Assert(originalRef);

    tempRef->Rewind();
    originalRef->Rewind();
    XIO::Copy(originalRef, tempRef, originalRef->Length(), parent->abortProc, parent->abortArg);

    try
    {
        parent->ioRef = tempRef;	// ! Fool UpdateFile into using the temp file.
        UpdateFile(false);
        parent->ioRef = originalRef;
    }
    catch (...)
    {
        parent->ioRef = originalRef;
        throw;
    }
    if (localProgressTracking) progressTracker->WorkComplete();
}