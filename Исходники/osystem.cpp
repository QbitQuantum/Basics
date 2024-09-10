void OSystem_Wii::setFeatureState(Feature f, bool enable) {
	switch (f) {
	case kFeatureFullscreenMode:
		_fullscreen = enable;
		setGraphicsMode(_activeGraphicsMode);
		break;
	default:
		break;
	}
}