    DWORD CALLBACK Thread()
    {
        static const int BufferSizeBytes = BufferSize * sizeof(T);

        while (waveout_running) {
            bool didsomething = false;
            for (u32 i = 0; i < numBuffers; i++) {
                if (!(whbuffer[i].dwFlags & WHDR_DONE))
                    continue;

                WAVEHDR *buf = whbuffer + i;

                buf->dwBytesRecorded = buf->dwBufferLength;

                T *t = (T *)buf->lpData;
                for (int p = 0; p < PacketsPerBuffer; p++, t += SndOutPacketSize)
                    SndBuffer::ReadSamples(t);

                whbuffer[i].dwFlags &= ~WHDR_DONE;
                waveOutWrite(hwodevice, buf, sizeof(WAVEHDR));
                didsomething = true;
            }

            if (didsomething)
                Sleep(1);
            else
                Sleep(0);
        }
        return 0;
    }