    bool Encode(float *input, UINT numInputFrames, DataPacket &packet, QWORD &timestamp)
    {
        if(bFirstFrame)
        {
            curEncodeTimestamp = timestamp;
            bFirstFrame = false;
        }

        //------------------------------------------------

        UINT lastSampleSize = frameCounter;

        frameCounter += numInputFrames;
        if(frameCounter > outputFrameSize)
        {
            frameCounter -= outputFrameSize;

            bufferedTimestamps << curEncodeTimestamp;
            curEncodeTimestamp = timestamp + ((outputFrameSize-lastSampleSize)*1000/App->GetSampleRateHz());
        }

        int ret = lame_encode_buffer_interleaved_ieee_float(lgf, (float*)input, numInputFrames, MP3OutputBuffer.Array()+1, dwMP3MaxSize);

        if(ret < 0)
        {
            AppWarning(TEXT("MP3 encode failed"));
            return false;
        }

        if(ret > 0)
        {
            if(bFirstPacket)
            {
                header.CopyArray(MP3OutputBuffer.Array(), ret);
                bFirstPacket = false;
                ret = 0;
            }
            else
            {
                packet.lpPacket = MP3OutputBuffer.Array();
                packet.size     = ret+1;

                timestamp = bufferedTimestamps[0];
                bufferedTimestamps.Remove(0);
            }
        }

        return ret > 0;
    }