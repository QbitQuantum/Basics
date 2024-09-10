void ConvexDecompositionDemo::clientMoveAndDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float dt = getDeltaTimeMicroseconds() * 0.000001f;

	m_dynamicsWorld->stepSimulation(dt);

	//optional but useful: debug drawing
	m_dynamicsWorld->debugDrawWorld();

	renderme();

	glFlush();
	swapBuffers();

}