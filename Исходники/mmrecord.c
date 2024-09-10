/**
 * Wave In Callback
 * Call back by Windows
 */
static void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, 
                                DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    MMRESULT mmReturn = 0;
    recorder_handle* hRecord = (recorder_handle*)dwInstance;
    DWORD recorded;
        
    if ((NULL == hRecord) || (NULL == hRecord->pHdr))
        return;

    JAVA_DEBUG_PRINT1("[record] waveInProc %d\n", hRecord->isRecording);

    if (uMsg != WIM_DATA)
        return;
    
    if (hRecord->hWAVEIN && hRecord->pHdr) {
        mmReturn = 
            waveInUnprepareHeader(hRecord->hWAVEIN, hRecord->pHdr, sizeof(WAVEHDR));
        if (MMSYSERR_NOERROR != mmReturn) 
            return;
    }

    if (hRecord->isRecording) {
        /* Write to file */
        recorded = hRecord->pHdr->dwBytesRecorded;
        if (recorded) {
            write_wav_file(hRecord, hRecord->pHdr->lpData, recorded);
        }
    
        /* Reuse input buffer */
        mmReturn = 
            waveInPrepareHeader(hRecord->hWAVEIN, hRecord->pHdr, sizeof(WAVEHDR));
        if (MMSYSERR_NOERROR == mmReturn) {
            mmReturn = 
                waveInAddBuffer(hRecord->hWAVEIN, hRecord->pHdr, sizeof(WAVEHDR));
        }
    
        if (MMSYSERR_NOERROR != mmReturn) {
            JAVA_DEBUG_PRINT("[record] Can't reuse input buffer\n");
        }

        return;
    }

    LocalFree(hRecord->pHdr->lpData);
    hRecord->pHdr->lpData = NULL;
    LocalFree(hRecord->pHdr);
    hRecord->pHdr = NULL;
}