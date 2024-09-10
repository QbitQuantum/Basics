void InputMonitor::Init(VideoOutputDevice* videoout, AudioOutputDevice* audioout) {
    ShutDown(); // Shut down devices and set them to NULL
    InnerSetVideoIn(m_Data->m_VID);
    InnerSetVideoOut(videoout);
    InnerSetAudioOut(audioout);
    AVController::Init();
}