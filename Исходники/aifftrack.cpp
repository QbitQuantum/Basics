bool AIFFTrack::play() {
	if (_stream) {
		Audio::RewindableAudioStream *stream = static_cast<Audio::RewindableAudioStream *>(_stream);
		if (!_looping) {
			stream->rewind();
		}
		return SoundTrack::play();
	}
	return false;
}