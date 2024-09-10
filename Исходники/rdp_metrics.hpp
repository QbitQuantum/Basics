    void set_server_cliprdr_metrics(InStream chunk, size_t length, uint32_t flags) {
        if (bool(flags & CHANNELS::CHANNEL_FLAG_FIRST)) {
            this->metrics->add_to_current_data(SERVER_CLIPBOARD_CHANNEL_DATA, length);
            RDPECLIP::CliprdrHeader header;
            header.recv(chunk);

            switch (header.msgType()) {
                case RDPECLIP::CB_FORMAT_LIST:
                    this->format_list_process(
                        chunk, header,
                        SERVER_TEXT_COPY_COUNT,
                        SERVER_IMAGE_COPY_COUNT,
                        SERVER_FILE_COPY_COUNT);
                    break;

                case RDPECLIP::CB_FORMAT_DATA_REQUEST:
                    this->process_format_data_request(
                        chunk,
                        ON_SERVER_TEXT_PASTE_COUNT,
                        ON_SERVER_IMAGE_PASTE_COUNT,
                        ON_SERVER_FILE_PASTE_COUNT);
                    break;

                case RDPECLIP::CB_FORMAT_DATA_RESPONSE:
                    this->process_format_data_response(header, ON_CLIENT_TOTAL_DATA_PASTE);
                    break;

                case RDPECLIP::CB_FILECONTENTS_REQUEST:
                    this->process_filecontents_request(chunk);
                    break;

                case RDPECLIP::CB_FILECONTENTS_RESPONSE:
                    this->process_filecontents_response(chunk, ON_CLIENT_TOTAL_DATA_PASTE);
                    break;
            }
        }
    }