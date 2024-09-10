static void callback(SLBufferQueueItf bufq, void *param)
{
    assert(NULL == param);
    if (!eof) {
        void *buffer = (char *)buffers + framesPerBuffer * sfframesize * which;
        ssize_t count = pipeReader->read(buffer, framesPerBuffer, (int64_t) -1);
        // on underrun from pipe, substitute silence
        if (0 >= count) {
            memset(buffer, 0, framesPerBuffer * sfframesize);
            count = framesPerBuffer;
            ++underruns;
        }
        if (count > 0) {
            SLuint32 nbytes = count * sfframesize;
            if (byteOrder != nativeByteOrder) {
                swab(buffer, buffer, nbytes);
            }
            if (transferFormat == AUDIO_FORMAT_PCM_8_BIT) {
                squeeze((short *) buffer, (unsigned char *) buffer, nbytes);
                nbytes /= 2;
            } else if (transferFormat == AUDIO_FORMAT_PCM_24_BIT_PACKED) {
                squeeze24((unsigned char *) buffer, (unsigned char *) buffer, nbytes);
                nbytes = nbytes * 3 / 4;
            }
            SLresult result = (*bufq)->Enqueue(bufq, buffer, nbytes);
            assert(SL_RESULT_SUCCESS == result);
            if (++which >= numBuffers)
                which = 0;
        }
    }
}