OsStatus CpPhoneMediaInterface::playAudio(const char* url,
                                          UtlBoolean repeat,
                                          UtlBoolean local,
                                          UtlBoolean remote)
{
    OsStatus returnCode = OS_NOT_FOUND;
    UtlString urlString;
    if(url) urlString.append(url);
    int fileIndex = urlString.index("file://");
    if(fileIndex == 0) urlString.remove(0, 6);

    if(mpFlowGraph && !urlString.isNull())
    {

        // Start playing the audio file
        returnCode = mpFlowGraph->playFile(urlString.data(),
            repeat,
            remote ? MpCallFlowGraph::TONE_TO_NET :
                MpCallFlowGraph::TONE_TO_SPKR);
    }

    if(returnCode != OS_SUCCESS)
    {
        osPrintf("Cannot play audio file: %s\n", urlString.data());
    }

    return(returnCode);
}