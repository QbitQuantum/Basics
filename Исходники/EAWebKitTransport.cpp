bool TransportHandlerFile::InitJob(TransportInfo* pTInfo, bool& bStateComplete)
{
    using namespace EA::WebKit;

    // We return true if we feel we can handle the job.
    FileSystem* pFS = GetFileSystem();

    if(pFS != NULL)
    {
        Allocator* pAllocator = GetAllocator();
        FileInfo*  pFileInfo  = new(pAllocator->Malloc(sizeof(FileInfo), 0, "EAWebKit/TransportHandlerFile")) FileInfo; 

        pTInfo->mTransportHandlerData = (uintptr_t)pFileInfo;
        bStateComplete = true;

        #ifdef EA_DEBUG
            mJobCount++;
        #endif

        sFileOpenJobCount++;

        return true;
    }

    return false;
}