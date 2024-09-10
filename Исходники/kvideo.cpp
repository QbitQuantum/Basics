reg_t kPlayDuck(EngineState *s, int argc, reg_t *argv) {
	uint16 operation = argv[0].toUint16();
	Video::VideoDecoder *videoDecoder = 0;
	bool reshowCursor = g_sci->_gfxCursor->isVisible();

	switch (operation) {
	case 1:	// Play
		// 6 params
		s->_videoState.reset();
		s->_videoState.fileName = Common::String::format("%d.duk", argv[1].toUint16());

		videoDecoder = new Video::AVIDecoder();

		if (!videoDecoder->loadFile(s->_videoState.fileName)) {
			warning("Could not open Duck %s", s->_videoState.fileName.c_str());
			break;
		}

		if (reshowCursor)
			g_sci->_gfxCursor->kernelHide();

		{
		// Duck videos are 16bpp, so we need to change the active pixel format
		int oldWidth = g_system->getWidth();
		int oldHeight = g_system->getHeight();
		Common::List<Graphics::PixelFormat> formats;
		formats.push_back(videoDecoder->getPixelFormat());
		initGraphics(640, 480, true, formats);

		if (g_system->getScreenFormat().bytesPerPixel != videoDecoder->getPixelFormat().bytesPerPixel)
			error("Could not switch screen format for the duck video");

		playVideo(videoDecoder, s->_videoState);

		// Switch back to 8bpp
		initGraphics(oldWidth, oldHeight, oldWidth > 320);
		}

		if (reshowCursor)
			g_sci->_gfxCursor->kernelShow();
		break;
	default:
		kStub(s, argc, argv);
		break;
	}

	return s->r_acc;
}