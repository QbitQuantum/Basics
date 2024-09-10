void GraspTest::displayCallback(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	if (m_dynamicsWorld)
		m_dynamicsWorld->debugDrawWorld();

//	drawLimit();

	renderme();

    glFlush();
    swapBuffers();
}