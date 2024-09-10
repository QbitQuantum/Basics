bool MMDeviceAudioSource::GetBuffer(float **buffer, UINT *numFrames, QWORD targetTimestamp)
{
    bool bSuccess = false;
    outputBuffer.Clear();

    if(!bBrokenTimestamp)
    {
        while(audioSegments.Num())
        {
            if(audioSegments[0].timestamp < targetTimestamp)
            {
                audioSegments[0].audioData.Clear();
                audioSegments.Remove(0);
            }
            else
                break;
        }
    }

    if(audioSegments.Num())
    {
        bool bUseSegment = false;

        AudioSegment &segment = audioSegments[0];

        QWORD difference = (segment.timestamp-targetTimestamp);
        if(bBrokenTimestamp || difference <= 10)
        {
            //Log(TEXT("segment.timestamp: %llu, targetTimestamp: %llu"), segment.timestamp, targetTimestamp);
            outputBuffer.TransferFrom(segment.audioData);
            audioSegments.Remove(0);

            bSuccess = true;
        }
    }

    outputBuffer.SetSize(441*2);

    *buffer = outputBuffer.Array();
    *numFrames = outputBuffer.Num()/2;

    return bSuccess;
}