void MFAudioEndpointControl::setActiveOutput(const QString &name)
{
    if (m_activeEndpoint == name)
        return;
    QMap<QString, LPWSTR>::iterator it = m_devices.find(name);
    if (it == m_devices.end())
        return;

    LPWSTR wstrID = *it;
    IMFActivate *activate = NULL;
    HRESULT hr = MFCreateAudioRendererActivate(&activate);
    if (FAILED(hr)) {
        qWarning() << "Failed to create audio renderer activate";
        return;
    }

    if (wstrID) {
        hr = activate->SetString(MF_AUDIO_RENDERER_ATTRIBUTE_ENDPOINT_ID, wstrID);
    } else {
        //This is the default one that has been inserted in updateEndpoints(),
        //so give the activate a hint that we want to use the device for multimedia playback
        //then the media foundation will choose an appropriate one.

        //from MSDN:
        //The ERole enumeration defines constants that indicate the role that the system has assigned to an audio endpoint device.
        //eMultimedia: Music, movies, narration, and live music recording.
        hr = activate->SetUINT32(MF_AUDIO_RENDERER_ATTRIBUTE_ENDPOINT_ROLE, eMultimedia);
    }

    if (FAILED(hr)) {
        qWarning() << "Failed to set attribute for audio device" << name;
        return;
    }

    if (m_currentActivate)
        m_currentActivate->Release();
    m_currentActivate = activate;
    m_activeEndpoint = name;
}