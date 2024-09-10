/* midiInputHandler - Low-level callback function to handle MIDI input.
 *      Installed by midiInOpen().  The input handler takes incoming
 *      MIDI events and places them in the circular input buffer.  It then
 *      notifies the application by posting a MM_MIDIINPUT message.
 *
 *      This function is accessed at interrupt time, so it should be as 
 *      fast and efficient as possible.  You can't make any
 *      Windows calls here, except PostMessage().  The only Multimedia
 *      Windows call you can make are timeGetSystemTime(), midiOutShortMsg().
 *      
 *
 * Param:   hMidiIn - Handle for the associated input device.
 *          wMsg - One of the MIM_***** messages.
 *          dwInstance - Points to CALLBACKINSTANCEDATA structure.
 *          dwParam1 - MIDI data.
 *          dwParam2 - Timestamp (in milliseconds)
 *
 * Return:  void
 */     
void FAR PASCAL midiInputHandler(
HMIDIIN hMidiIn, 
WORD wMsg, 
DWORD dwInstance, 
DWORD dwParam1, 
DWORD dwParam2)
{
    EVENT event;
    
    switch(wMsg)
    {
        case MIM_OPEN:
            break;

        /* The only error possible is invalid MIDI data, so just pass
         * the invalid data on so we'll see it.
         */
        case MIM_ERROR:
        case MIM_DATA:
            event.fdwEvent = (wMsg == MIM_ERROR) ? EVNT_F_ERROR : 0;
            event.dwDevice = ((LPCALLBACKINSTANCEDATA)dwInstance)->dwDevice;
            event.data = dwParam1;
#ifdef MIDI_TIMESTAMP
            event.timestamp = timeGetSystemTime();
#endif
            /* Put the MIDI event in the circular input buffer.
             */

            PutEvent(((LPCALLBACKINSTANCEDATA)dwInstance)->lpBuf,
                       (LPEVENT) &event); 

            break;

        default:
            break;
    }
}