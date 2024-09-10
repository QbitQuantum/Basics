static void midi_flush_current_buffer(void)
{
    MMRESULT rv;
    MIDIEVENT * evt;
    BOOL needsPrepare = FALSE;

    if (!currentMidiBuffer) {
        return;
    }

    evt = (MIDIEVENT *) currentMidiBuffer->hdr.lpData;

    if (!midiThread) {
        // immediate messages don't use a MIDIEVENT header so strip it off and
        // make some adjustments

        currentMidiBuffer->hdr.dwBufferLength = currentMidiBuffer->hdr.dwBytesRecorded - 12;
        currentMidiBuffer->hdr.dwBytesRecorded = 0;
        currentMidiBuffer->hdr.lpData = (LPSTR) &evt->dwParms[0];
        
        if (currentMidiBuffer->hdr.dwBufferLength > 0) {
            needsPrepare = TRUE;
        }
    } else {
        needsPrepare = TRUE;
    }
    
    if (needsPrepare) {
        // playing a file, or sending a sysex when not playing means
        // we need to prepare the buffer
        rv = midiOutPrepareHeader( (HMIDIOUT) midiStream, &currentMidiBuffer->hdr, sizeof(MIDIHDR) );
        if (rv != MMSYSERR_NOERROR) {
            midi_error(rv, "WinMM midi_flush_current_buffer midiOutPrepareHeader");
            return;
        }

        currentMidiBuffer->prepared = TRUE;
    }

    if (midiThread) {
        // midi file playing, so send events to the stream

        LL_Add( (MidiBuffer*) &activeMidiBuffers, currentMidiBuffer, next, prev );

        rv = midiStreamOut(midiStream, &currentMidiBuffer->hdr, sizeof(MIDIHDR));
        if (rv != MMSYSERR_NOERROR) {
            midi_error(rv, "WinMM midi_flush_current_buffer midiStreamOut");
            midi_dispose_buffer(currentMidiBuffer, "midi_flush_current_buffer");
            return;
        }

        //fprintf(stderr, "WinMM midi_flush_current_buffer queued buffer %p\n", currentMidiBuffer);
    } else {
        // midi file not playing, so send immediately
        
        if (currentMidiBuffer->hdr.dwBufferLength > 0) {
            rv = midiOutLongMsg( (HMIDIOUT) midiStream, &currentMidiBuffer->hdr, sizeof(MIDIHDR) );
            if (rv == MMSYSERR_NOERROR) {
                // busy-wait for Windows to be done with it
                while (!(currentMidiBuffer->hdr.dwFlags & MHDR_DONE)) ;
                
                //fprintf(stderr, "WinMM midi_flush_current_buffer sent immediate long\n");
            } else {
                midi_error(rv, "WinMM midi_flush_current_buffer midiOutLongMsg");
            }
        } else {
            rv = midiOutShortMsg( (HMIDIOUT) midiStream, evt->dwEvent );
            if (rv == MMSYSERR_NOERROR) {
                //fprintf(stderr, "WinMM midi_flush_current_buffer sent immediate short\n");
            } else {
                midi_error(rv, "WinMM midi_flush_current_buffer midiOutShortMsg");
            }
        }

        midi_dispose_buffer(currentMidiBuffer, "midi_flush_current_buffer");
    }
    
    currentMidiBuffer = 0;
}