as_Sound::as_Sound(char *fileName)
{
    long rc = 0;
    long len = 0;
    HRESULT hr;
    WCHAR wChar[MAX_PATH];

    if (NULL == fileName)
        return;

    pSegment = NULL;
    pState = NULL;
    pDS3DBuffer = NULL;
    pAudioPath = NULL;
    memset(&dmod, 0, sizeof(DMUS_OBJECTDESC));
    gain = 1.0f;
    Direction[0] = 0.0f;
    Direction[1] = 0.0f;
    Direction[2] = 0.0f;
    Position[0] = 0.0f;
    Position[1] = 0.0f;
    Position[2] = 0.0f;

    // Create a 3D audiopath with a 3d buffer.
    // We can then play all segments into this buffer and directly control its 3D parameters.
    hr = g_pPerformance->CreateStandardAudioPath(
        DMUS_APATH_DYNAMIC_3D,
        1,
        TRUE,
        &(this->pAudioPath));
    if (FAILED(hr))
    {
        char msg[MSG_LEN];
        sprintf(msg, "Could not create standard audio path, error 0x%08lX", hr);
        AddLogMsg(msg);
        return;
    }

    // Get the 3D buffer in the audio path.
    hr = this->pAudioPath->GetObjectInPath(
        0,
        DMUS_PATH_BUFFER,
        0,
        GUID_NULL,
        0,
        IID_IDirectSound3DBuffer,
        (LPVOID *)&this->pDS3DBuffer);
    if (FAILED(hr))
    {
        AddLogMsg("Error: GetObjectInPath");
        return;
    }
    this->pAudioPath->SetVolume(0, 0);

    dmod.dwSize = sizeof(DMUS_OBJECTDESC);
    dmod.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME | DMUS_OBJ_FULLPATH;
    dmod.guidClass = CLSID_DirectMusicSegment;

    len = strlen(fileName);
    rc = mbstowcs(wChar, fileName, len + 1);
    wcscpy(dmod.wszFileName, wChar);

    hr = g_Loader->GetObject(&dmod, IID_IDirectMusicSegment8, (void **)&pSegment);
    if (FAILED(hr))
    {
        AddLogMsg("Could not get object: IID_IDirectMusicSegment8");
        return;
    }
    hr = pSegment->Download(g_pPerformance);
    if (FAILED(hr))
    {
        AddLogMsg("Could not download segment");
        return;
    }
    this->status = STATUS_INITIAL;
}