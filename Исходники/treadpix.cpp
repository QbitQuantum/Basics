void
ReadPixSanityTest::checkStencil(ReadPixSanityResult& r, Window& w) {
	DrawingSurfaceConfig& config = *r.config;
	RandomBits sRand(config.s, 10101);

	r.passStencil = true;
	for (int i = 0; i < 100 && r.passStencil; ++i) {
		GLuint expected = sRand.next();
		glClearStencil(expected);
		glClear(GL_STENCIL_BUFFER_BIT);

		GLuint buf[READPIX_SANITY_WIN_SIZE][READPIX_SANITY_WIN_SIZE];
		glReadPixels(0, 0, READPIX_SANITY_WIN_SIZE,
			READPIX_SANITY_WIN_SIZE, GL_STENCIL_INDEX,
			GL_UNSIGNED_INT, buf);

		for (int y = 0; y < READPIX_SANITY_WIN_SIZE && r.passStencil;
		    ++y)
			for (int x = 0; x < READPIX_SANITY_WIN_SIZE; ++x)
				if (buf[y][x] != expected) {
					r.passStencil = false;
					r.xStencil = x;
					r.yStencil = y;
					r.expectedStencil = expected;
					r.actualStencil = buf[y][x];
					break;
				}

		w.swap();
	}
} // ReadPixSanityTest::checkStencil