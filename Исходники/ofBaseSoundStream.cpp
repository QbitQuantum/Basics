void ofBaseSoundStream::applySoundStreamOriginInfo( ofSoundBuffer& buffer ) {
	buffer.tickCount = getTickCount();
	buffer.soundStreamDeviceID = getDeviceID();
}