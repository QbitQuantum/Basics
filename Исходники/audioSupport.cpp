void writeAudioBlock(HWAVEOUT hWaveOut, LPSTR block, DWORD size)
{
    WAVEHDR header;
    /*
    * initialise the block header with the size
    * and pointer.
    */
    ZeroMemory(&header, sizeof(WAVEHDR));
    header.dwBufferLength = size;
    header.lpData = block;
    /*
    * prepare the block for playback
    */
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    /*
    * write the block to the device. waveOutWrite returns immediately
    * unless a synchronous driver is used (not often).
    */
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    /*
    * wait a while for the block to play then start trying
    * to unprepare the header. this will fail until the block has
    * played.
    */
    Sleep(500);
    while(waveOutUnprepareHeader(
    hWaveOut, 
    &header, 
    sizeof(WAVEHDR)
    ) == WAVERR_STILLPLAYING)
    Sleep(100);
}