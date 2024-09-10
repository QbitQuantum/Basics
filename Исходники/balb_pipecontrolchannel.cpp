int PipeControlChannel::readNamedPipe()
{
    BALL_LOG_SET_CATEGORY(LOG_CATEGORY);
    BSLS_ASSERT(INVALID_HANDLE_VALUE != d_impl.d_windows.d_handle);

    BALL_LOG_TRACE << "Accepting next pipe client connection" << BALL_LOG_END;

    if (!ConnectNamedPipe(d_impl.d_windows.d_handle, NULL)) {
        BALL_LOG_TRACE << "Connecting to named pipe '" << d_pipeName
                       << "': "
                       << describeWin32Error(GetLastError())
                       << BALL_LOG_END;

        DWORD lastError = GetLastError();
        if (lastError != ERROR_PIPE_CONNECTED && lastError != ERROR_NO_DATA) {
            BALL_LOG_TRACE << "Failed to connect to named pipe '" << d_pipeName
                           << "'"
                           << BALL_LOG_END;
            return -1;
        }
    }

    while(1) {
        char buffer[MAX_PIPE_BUFFER_LEN];
        DWORD bytesRead = 0;

        if (ReadFile(d_impl.d_windows.d_handle,
                     buffer,
                     MAX_PIPE_BUFFER_LEN,
                     &bytesRead,
                     NULL))
        {
           if (bytesRead > 0) {
               if (buffer[bytesRead - 1] == '\n') {
                   bytesRead--;
               }
               bslstl::StringRef stringRef(buffer, bytesRead);
               if (!stringRef.isEmpty()) {
                   d_callback(stringRef);
               }
           }
           else {
              // reached EOF on a named pipe.
              break;
           }
        }
        else {
            BALL_LOG_TRACE << "Failed to read from named pipe '" << d_pipeName
                           << "': "
                           << describeWin32Error(GetLastError())
                           << BALL_LOG_END;
            break;
        }
    }

    DisconnectNamedPipe(d_impl.d_windows.d_handle);

    return 0;
}