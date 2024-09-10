LIBFREESPACE_API int freespace_openDevice(FreespaceDeviceId id) {
    int idx;
    struct FreespaceDeviceStruct* device = freespace_private_getDeviceById(id);
    if (device == NULL) {
        return FREESPACE_ERROR_NO_DEVICE;
    }

    if (device->isOpened_) {
        // Each device can only be opened once.
        return FREESPACE_ERROR_BUSY;
    }


    for (idx = 0; idx < device->handleCount_; idx++) {
        struct FreespaceSubStruct* s = &device->handle_[idx];
        if (s->handle_ != NULL) {
            // Device was partially (incorrectly) opened.
            freespace_private_forceCloseDevice(device);
            return FREESPACE_ERROR_BUSY;
        }
        if (s->devicePath == NULL) {
            // Device was not fully enumerated.
            freespace_private_forceCloseDevice(device);
            return FREESPACE_ERROR_NO_DEVICE;
        }
        DEBUG_WPRINTF(L"Open %s\n", s->devicePath);
        s->handle_ = CreateFile(s->devicePath,
                                GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                NULL,
                                OPEN_EXISTING,
                                FILE_FLAG_OVERLAPPED,
                                NULL);
        {
            DWORD d;
            if (!GetHandleInformation(s->handle_, &d)) {
                // We do not have the correct handle.
                DEBUG_PRINTF("freespace_openDevice failed with code %d\n", GetLastError());
            }
        }

        if (s->handle_ == INVALID_HANDLE_VALUE) {
            freespace_private_forceCloseDevice(device);
            return FREESPACE_ERROR_NO_DEVICE;
        }

        if (!BindIoCompletionCallback(s->handle_, freespace_private_overlappedCallback, 0)) {
            freespace_private_forceCloseDevice(device);
            return FREESPACE_ERROR_UNEXPECTED;
        }

        if (!HidD_SetNumInputBuffers(s->handle_, HID_NUM_INPUT_BUFFERS)) {
            freespace_private_forceCloseDevice(device);
            return FREESPACE_ERROR_NO_DEVICE;
        }

        // Create the read event.
        s->readOverlapped_.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (s->readOverlapped_.hEvent == NULL) {
            freespace_private_forceCloseDevice(device);
            return FREESPACE_ERROR_UNEXPECTED;
        }
        s->readOverlapped_.Offset = 0;
        s->readOverlapped_.OffsetHigh = 0;
        s->readStatus_ = FALSE;
    }

    device->isOpened_ = TRUE;

    // Enable send by initializing all send events.
    for (idx = 0; idx < FREESPACE_MAXIMUM_SEND_MESSAGE_COUNT; idx++) {
        device->send_[idx].overlapped_.hEvent = NULL;
        if (initializeSendStruct(&device->send_[idx]) != FREESPACE_SUCCESS) {
            freespace_private_forceCloseDevice(device);
            return FREESPACE_ERROR_UNEXPECTED;
        }
    }

    // If async mode has been enabled already, then start the receive
    // process going.
    if (freespace_instance_->fdAddedCallback_) {
        int rc;
        rc = initiateAsyncReceives(device);
        if (rc != FREESPACE_SUCCESS) {
            freespace_private_forceCloseDevice(device);
            return rc;
        }
    }

    return FREESPACE_SUCCESS;
}