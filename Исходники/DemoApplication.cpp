// called synchronous from ogre update loop after of updating updating all sceneNodes controlled by a physic body  
void DemoApplication::OnRenderUpdateEnd(dFloat updateParam)
{
	// set the camera interpolated matrix
	Matrix4 matrix;
	Vector3 cameraPosit;
	Quaternion cameraRotation;
	
	// interpolate the camera matrix at rendering time
	m_cameraSmoothing.InterpolateMatrix (updateParam, &matrix[0][0]);
	matrix = matrix.transpose();
	mCamera->setPosition (matrix.getTrans());
	mCamera->setOrientation (matrix.extractQuaternion());

	// show statistic and help options
	m_onScreeHelp.Update (m_keyboard->isKeyDown(OIS::KC_F1) ? true : false);
	if (m_onScreeHelp.m_state) {
		int row = 0;
		const RenderTarget::FrameStats& stats = mWindow->getStatistics();
		row = m_screen->write(20, row + 20, "FPS:  %05.3f", stats.lastFPS);
		row = m_screen->write(20, row + 20, "Physics time:  %05.3f ms", float (double (m_physicsWorld->GetPhysicsTimeInMicroSeconds()) * 1.0e-3f));
		row = m_screen->write(20, row + 20, "Number of rigid bodies:  %d", m_physicsWorld->GetBodyCount());
		row = m_screen->write(20, row + 20, "F1:  Hide debug help text");
		row = m_screen->write(20, row + 20, "F2:  Toggle %s simulation update", m_physicsWorld->GetConcurrentUpdateMode() ? "Asynchronous" : "Synchronous");
		row = m_screen->write(20, row + 20, "F3:  Toggle display physic debug");
		row = m_screen->write(20, row + 30, "W, S, A, D:  Free camera navigation");
		row = m_screen->write(20, row + 20, "Hold CTRL and Left Mouse Key:  Show mouse cursor and pick objects from the screen");
		row = m_screen->write(20, row + 20, "ESC:  Exit application");
	} else {
		m_screen->removeAll();
	}
	m_screen->update();

	// see if debug display was activated
	m_debugTriggerKey.Update (m_keyboard->isKeyDown(OIS::KC_F3) ? true : false);
	if (m_debugTriggerKey.TriggerUp()) {
		GetPhysics()->WaitForUpdateToFinish();
	}
	m_debugRender->SetDebugMode (m_debugTriggerKey.m_state);

	// check if the player want to run the physics concurrent of not 
	m_asyncronousUpdateKey.Update (m_keyboard->isKeyDown(OIS::KC_F2) ? true : false);
	if (m_asyncronousUpdateKey.TriggerUp()) {
		GetPhysics()->WaitForUpdateToFinish();
		m_physicsWorld->SetConcurrentUpdateMode(!m_physicsWorld->GetConcurrentUpdateMode());
	}
}