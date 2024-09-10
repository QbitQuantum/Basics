void TextTrackList::remove(TextTrack* track)
{
    Vector<RefPtr<TextTrack> >* tracks = 0;
    RefPtr<InbandTextTrack> inbandTrack;

    if (track->trackType() == TextTrack::TrackElement) {
        tracks = &m_elementTracks;
    } else if (track->trackType() == TextTrack::AddTrack) {
        tracks = &m_addTrackTracks;
    } else if (track->trackType() == TextTrack::InBand) {
        tracks = &m_inbandTracks;
        inbandTrack = static_cast<InbandTextTrack*>(track);
    } else {
        ASSERT_NOT_REACHED();
    }

    size_t index = tracks->find(track);
    if (index == kNotFound)
        return;

    invalidateTrackIndexesAfterTrack(track);

    ASSERT(track->mediaElement() == m_owner);
    track->setMediaElement(0);

    tracks->remove(index);

    if (inbandTrack)
        inbandTrack->trackRemoved();
}