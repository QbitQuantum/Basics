// buffer source stuff
void BufferSourceThread::handleBuffer(sp<GraphicBuffer> &graphic_buffer, uint8_t *buffer, unsigned int count) {
    int size;
    buffer_info_t info;
    int fd = -1;
    char fn[256];

    if (!graphic_buffer.get()) {
        printf("Invalid graphic_buffer!\n");
        return;
    }

    size = calcBufSize((int)graphic_buffer->getPixelFormat(),
                              graphic_buffer->getWidth(),
                              graphic_buffer->getHeight());
    if (size <= 0) {
        printf("Can't get size!\n");
        return;
    }

    if (!buffer) {
        printf("Invalid mapped buffer!\n");
        return;
    }

    info.size = size;
    info.width = graphic_buffer->getWidth();
    info.height = graphic_buffer->getHeight();
    info.format = graphic_buffer->getPixelFormat();
    info.buf = graphic_buffer;

    {
        Mutex::Autolock lock(mReturnedBuffersMutex);
        if (mReturnedBuffers.size() >= kReturnedBuffersMaxCapacity) mReturnedBuffers.removeAt(0);
    }
    mReturnedBuffers.add(info);

    // Do not write buffer to file if we are streaming capture
    // It adds too much latency
    if (!mRestartCapture) {
        fn[0] = 0;
        sprintf(fn, "/sdcard/img%03d.raw", count);
        fd = open(fn, O_CREAT | O_WRONLY | O_TRUNC, 0777);
        if (fd >= 0) {
            if (size != write(fd, buffer, size)) {
                printf("Bad Write int a %s error (%d)%s\n", fn, errno, strerror(errno));
            }
            printf("%s: buffer=%08X, size=%d stored at %s\n",
                        __FUNCTION__, (int)buffer, info.size, fn);
            close(fd);
        } else {
            printf("error opening or creating %s\n", fn);
        }
    }
}