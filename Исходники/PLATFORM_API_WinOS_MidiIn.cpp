//$$fb dwParam1 holds a pointer for long messages. How can that be a DWORD then ???
void CALLBACK MIDI_IN_PutMessage( HMIDIIN hMidiIn, UINT wMsg, UINT_PTR dwInstance, UINT_PTR dwParam1, UINT_PTR dwParam2 ) {

    MidiDeviceHandle* handle = (MidiDeviceHandle*) dwInstance;

    TRACE3("> MIDI_IN_PutMessage, hMidiIn: %x, wMsg: %x, dwInstance: %x\n", hMidiIn, wMsg, dwInstance);
    TRACE2("                      dwParam1: %x, dwParam2: %x\n", dwParam1, dwParam2);

    switch(wMsg) {

    case MIM_OPEN:
        TRACE0("< MIDI_IN_PutMessage: MIM_OPEN\n");
        break;

    case MIM_CLOSE:
        TRACE0("< MIDI_IN_PutMessage: MIM_CLOSE\n");
        break;

    case MIM_MOREDATA:
    case MIM_DATA:
        TRACE3("  MIDI_IN_PutMessage: MIM_MOREDATA or MIM_DATA. status=%x  data1=%x  data2=%x\n",
               dwParam1 & 0xFF, (dwParam1 & 0xFF00)>>8, (dwParam1 & 0xFF0000)>>16);
        if (handle!=NULL && handle->queue!=NULL && handle->platformData) {
            MIDI_QueueAddShort(handle->queue,
                               // queue stores packedMsg in big endian
                               //(dwParam1 << 24) | ((dwParam1 << 8) & 0xFF0000) | ((dwParam1 >> 8) & 0xFF00),
                               (UINT32) dwParam1,
                               // queue uses microseconds
                               ((INT64) dwParam2)*1000,
                               // overwrite if queue is full
                               TRUE);
            SetEvent((HANDLE) handle->platformData);
        }
        TRACE0("< MIDI_IN_PutMessage\n");
        break;

    case MIM_LONGDATA:
        TRACE1("  MIDI_IN_PutMessage: MIM_LONGDATA (%d bytes recorded)\n", (int) (((MIDIHDR*) dwParam1)->dwBytesRecorded));
        if (handle!=NULL && handle->queue!=NULL && handle->platformData) {
            MIDIHDR* hdr = (MIDIHDR*) dwParam1;
            TRACE2("  MIDI_IN_PutMessage: Adding to queue: index %d, %d bytes\n", (INT32) hdr->dwUser, hdr->dwBytesRecorded);
            MIDI_QueueAddLong(handle->queue,
                              (UBYTE*) hdr->lpData,
                              (UINT32) hdr->dwBytesRecorded,
                              // sysex buffer index
                              (INT32) hdr->dwUser,
                              // queue uses microseconds
                              ((INT64) dwParam2)*1000,
                              // overwrite if queue is full
                              TRUE);
            SetEvent((HANDLE) handle->platformData);
        }
        TRACE0("< MIDI_IN_PutMessage\n");
        break;

    case MIM_ERROR:
        ERROR0("< MIDI_IN_PutMessage: MIM_ERROR!\n");
        break;

    case MIM_LONGERROR:
        if (dwParam1 != 0) {
            MIDIHDR* hdr = (MIDIHDR*) dwParam1;
#ifdef USE_TRACE
            if (hdr->dwBytesRecorded > 0) {
                TRACE2("  MIDI_IN_PutMessage: MIM_LONGERROR! recorded: %d bytes with status 0x%2x\n",
                        hdr->dwBytesRecorded, (int) (*((UBYTE*) hdr->lpData)));
            }
#endif
            // re-add hdr to device query
            hdr->dwBytesRecorded = 0;
            midiInAddBuffer((HMIDIIN)handle->deviceHandle, hdr, sizeof(MIDIHDR));
        }
        ERROR0("< MIDI_IN_PutMessage: MIM_LONGERROR!\n");
        break;

    default:
        ERROR1("< MIDI_IN_PutMessage: ERROR unknown message %d!\n", wMsg);
        break;

    } // switch (wMsg)
}