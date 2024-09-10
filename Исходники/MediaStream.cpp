bool MediaStream::removeTrack(PassRefPtr<MediaStreamTrack> prpTrack)
{
    // This is a common part used by removeTrack called by JavaScript
    // and removeRemoteTrack and only removeRemoteTrack must fire removetrack event
    RefPtr<MediaStreamTrack> track = prpTrack;
    Vector<RefPtr<MediaStreamTrack>>* tracks = trackVectorForType(track->source()->type());

    size_t pos = tracks->find(track);
    if (pos == notFound)
        return false;

    tracks->remove(pos);
    m_private->removeTrack(&track->privateTrack());
    // There can be other tracks using the same source in the same MediaStream,
    // like when MediaStreamTrack::clone() is called, for instance.
    // Spec says that a source can be shared, so we must assure that there is no
    // other track using it.
    if (!haveTrackWithSource(track->source()))
        m_private->removeSource(track->source());

    track->removeObserver(this);
    if (!m_audioTracks.size() && !m_videoTracks.size())
        setActive(false);

    return true;
}