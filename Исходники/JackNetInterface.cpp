    int JackNetSlaveInterface::DataRecv()
    {
        int rx_bytes = 0;
        uint recvd_midi_pckt = 0;
        packet_header_t* rx_head = reinterpret_cast<packet_header_t*>(fRxBuffer);

        while (!fRxHeader.fIsLastPckt) {
            // how much data is queued on the rx buffer ?
            rx_bytes = Recv(fParams.fMtu, MSG_PEEK);

            // error here, just skip the cycle (return -1)
            if (rx_bytes == SOCKET_ERROR) {
                return rx_bytes;
            }

            if (rx_bytes && (rx_head->fDataStream == 's') && (rx_head->fID == fParams.fID)) {
                // read data
                switch (rx_head->fDataType) {

                    case 'm':   // midi
                        rx_bytes = MidiRecv(rx_head, fNetMidiCaptureBuffer, recvd_midi_pckt);
                        break;

                    case 'a':   // audio
                        rx_bytes = AudioRecv(rx_head, fNetAudioCaptureBuffer);
                        break;

                    case 's':   // sync
                        jack_info("NetSlave : missing last data packet");
                        return FinishRecv(fNetAudioCaptureBuffer);
                }
            }
        }

        fRxHeader.fCycle = rx_head->fCycle;
        return rx_bytes;
    }