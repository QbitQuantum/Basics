static bool at_vrecv(const char *response, va_list args)
{
    char *_buffer = at._buffer;
    char *_recv_delimiter = at._recv_delimiter;
    char c;
    int  ret = 0;
vrecv_start:
    while (response[0]) {
        int i = 0;
        int offset = 0;

        while (response[i]) {
            if (memcmp(&response[i + 1 - at._recv_delim_size], _recv_delimiter,
                       at._recv_delim_size) == 0) {
                i++;
                break;
            } else if (response[i] == '%' && response[i + 1] != '%' &&
                       response[i + 1] != '*') {
                _buffer[offset++] = '%';
                _buffer[offset++] = '*';
                i++;
            } else {
                _buffer[offset++] = response[i++];
            }
        }

        _buffer[offset++] = '%';
        _buffer[offset++] = 'n';
        _buffer[offset++] = 0;

        int j = 0;

        while (true) {
            ret = at_getc(&c);
            if (ret != 0) {
                return false;
            }
            _buffer[offset + j++] = c;
            _buffer[offset + j] = 0;

            for (int k = 0; k < at._oobs_num; k++) {
                oob_t *oob = &(at._oobs[k]);
                if (j == oob->len &&
                    memcmp(oob->prefix, at._buffer + offset, oob->len) == 0) {
                    LOGD(MODULE_NAME, "AT! %s\r\n", oob->prefix);
                    oob->cb(oob->arg);

                    goto vrecv_start;
                }
            }

            int count = -1;
            sscanf(_buffer + offset, _buffer, &count);

            if (count == j) {
                LOGD(MODULE_NAME, "AT= %s\r\n", _buffer + offset);
                memcpy(_buffer, response, i);
                _buffer[i] = 0;
                vsscanf(_buffer + offset, _buffer, args);
                response += i;
                break;
            }

            if (j + 1 >= BUFFER_SIZE - offset ||
                strcmp(&_buffer[offset + j - at._recv_delim_size],
                       _recv_delimiter) == 0) {
                LOGD(MODULE_NAME, "AT< %s", _buffer + offset);
                j = 0;
            }
        }
    }

    return true;
}