bool glCheck() {
	if (int err = glGetError()) {
		LogF("GL error %d: %s", err, gluErrorString(err));
		return false;
	}
	return true;
}