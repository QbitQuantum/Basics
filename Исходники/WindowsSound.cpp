bool WindowsSound::Init()
{
    HRESULT hr;

    //create the sound device
    hr = DirectSoundCreate8(NULL, &(this->directSoundDevice), NULL);
    if(FAILED(hr))
        return false;

    //set cooperative level to PRIORITY (=high)
    HWND hwndC = GetConsoleWindow() ;
    hr = this->directSoundDevice->SetCooperativeLevel(hwndC, DSSCL_PRIORITY);
    if(FAILED(hr))
        return false;

    //create an output wave format
    WAVEFORMATEX waveFormat;
    memset(&waveFormat, 0, sizeof(WAVEFORMATEX));
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = CHANNELS_NUMBER;
    waveFormat.nSamplesPerSec = SAMPLE_RATE;
    waveFormat.wBitsPerSample = BITS_PER_SAMPLE;
    waveFormat.nBlockAlign = BLOCK_ALIGN;
    waveFormat.nAvgBytesPerSec = AVERAGE_BYTES_PER_SECOND; //msdn recommendation for PCM format

    //Primary sound buffer
    DSBUFFERDESC bufferDesc;
    memset(&bufferDesc, 0, sizeof(DSBUFFERDESC));
    bufferDesc.dwSize = sizeof(DSBUFFERDESC);
    bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER|DSBCAPS_STICKYFOCUS;
    bufferDesc.dwBufferBytes = 0;
    bufferDesc.lpwfxFormat = NULL;

    LPDIRECTSOUNDBUFFER primaryDirectSoundBuffer;
    hr = this->directSoundDevice->CreateSoundBuffer(&bufferDesc, &primaryDirectSoundBuffer, NULL);
    if(FAILED(hr))
        return false;
    hr = primaryDirectSoundBuffer->SetFormat(&waveFormat);
    if(FAILED(hr))
        return false;

    //set up a buffer description
    DSBUFFERDESC soundBufferDescription;
    memset(&soundBufferDescription, 0, sizeof(DSBUFFERDESC));
    soundBufferDescription.dwSize = sizeof(DSBUFFERDESC);
    //DSBCAPS_STICKYFOCUS: allows to play sound even if we don't have have focus.
    //DSBCAPS_GETCURRENTPOSITION2: tells DirectSound we'll use the GetPosition method later on that sound buffer.
    soundBufferDescription.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STICKYFOCUS;
    soundBufferDescription.dwBufferBytes = BUFFER_LENGTH_IN_BYTES;
    soundBufferDescription.lpwfxFormat = &waveFormat;

    //create the sound buffer
    hr = this->directSoundDevice->CreateSoundBuffer(&soundBufferDescription, &(this->directSoundBuffer), NULL);
    if(FAILED(hr))
        return false;

    return true;

}