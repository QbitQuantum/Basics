SLresult AudioOutput::stop() {
    ALOGI("Set the audio player state paused");
    // Set the audio player state playing
    SLresult result = setAudioPlayerStatePaused();
    if (SL_RESULT_SUCCESS != result) {
        return result;
    }
    playingState = PLAYING_STATE_STOPPED;
    usleep(0.05 * 1000000);
    ALOGI("destroyContext...");
    destroyContext();
}