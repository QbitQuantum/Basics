void VideoWrapper::produceCycled(void)
{
    VideoEventUnrecPtr TheEvent = VideoEvent::create(VideoWrapperRefPtr(this), getSystemTime());
	VideoListenerSet Listeners(_VideoListeners);
    for(VideoListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->cycled(TheEvent);
    }
    _Producer.produceEvent(VideoCycledMethodId,TheEvent);
}