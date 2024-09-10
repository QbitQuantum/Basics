ModalIntro::ModalIntro() {
	_field_8 = 0;
	_countDown = 0;
	_stillRunning = 0;

	if (g_vars->sceneIntro_skipIntro) {
		_introFlags = 4;
	} else {
		_introFlags = 33;
		_countDown = 150;

		PictureObject *pict = g_fullpipe->accessScene(SC_INTRO1)->getPictureObjectById(PIC_IN1_PIPETITLE, 0);
		pict->setFlags(pict->_flags & 0xFFFB);
	}

	g_vars->sceneIntro_skipIntro = false;
	_sfxVolume = g_fullpipe->_sfxVolume;
}