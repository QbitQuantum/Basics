void plAudioFileReader::ICacheFile(const char* path, bool noOverwrite, plAudioCore::ChannelSelect whichChan)
{
    char cachedPath[256];
    IGetCachedPath(path, cachedPath, whichChan);
    if (!noOverwrite || !plFileUtils::FileExists(cachedPath))
    {
        plAudioFileReader* reader = plAudioFileReader::CreateReader(path, whichChan, kStreamNative);
        if (!reader || !reader->IsValid())
        {
            delete reader;
            return;
        }
        plAudioFileReader* writer = CreateWriter(cachedPath, reader->GetHeader());
        if (!writer || !writer->IsValid())
        {
            delete reader;
            delete writer;
            return;
        }

        uint8_t buffer[4096];
        uint32_t numLeft;
        while ((numLeft = reader->NumBytesLeft()) > 0)
        {
            uint32_t toRead = (numLeft < sizeof(buffer)) ? numLeft : sizeof(buffer);
            reader->Read(toRead, buffer);
            writer->Write(toRead, buffer);
        }
        writer->Close();

        delete writer;
        delete reader;
    }
}