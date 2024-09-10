int GEngine::gameLoop() {

	if (m_errorState == true) {
		setErrorDetails(
				"Cannot enter game loop when the engine is in a error state");
		return -1;
	}

	m_GameActive = true;
	m_physicsActive = true;

	m_clock.initialize();
	float secondsPassed;

	while (m_GameActive) {

		secondsPassed = m_clock.calculateElapsedTime();

		//Alert to the FPS calculator of a new frame
		m_fpsCalculator.frame(secondsPassed);

		//Run through the postbox and trigger events
		while (m_inputPostbox.HasNext()) {

			processEvent(m_inputPostbox.ReadNext());

		}

		doFrameUpdate(secondsPassed);

		//Rendering Step

		GRenderer::getRenderer()->renderScene(m_canvasWidth, m_canvasHeight);

		//End of rendering step

		//Sleep
		f_sleep();
	}

	return 0;
}