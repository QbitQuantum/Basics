void SerializeDemo::clientMoveAndDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	//simple dynamics world doesn't handle fixed-time-stepping
	float ms = getDeltaTimeMicroseconds();
	
	///step the simulation
	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(ms / 1000000.f);

		
#ifdef DESERIALIZE_SOFT_BODIES
		if (fSoftBodySolver)
            fSoftBodySolver->copyBackToSoftBodies();
#endif

		m_dynamicsWorld->debugDrawWorld();

#ifdef DESERIALIZE_SOFT_BODIES
		if (m_dynamicsWorld->getWorldType()==BT_SOFT_RIGID_DYNAMICS_WORLD)
		{
			//optional but useful: debug drawing
			btSoftRigidDynamicsWorld* softWorld = (btSoftRigidDynamicsWorld*)m_dynamicsWorld;

			for (  int i=0;i<softWorld->getSoftBodyArray().size();i++)
			{
				btSoftBody*	psb=(btSoftBody*)softWorld->getSoftBodyArray()[i];
				if (softWorld->getDebugDrawer() && !(softWorld->getDebugDrawer()->getDebugMode() & (btIDebugDraw::DBG_DrawWireframe)))
				{
					btSoftBodyHelpers::DrawFrame(psb,softWorld->getDebugDrawer());
					btSoftBodyHelpers::Draw(psb,softWorld->getDebugDrawer(),softWorld->getDrawFlags());
				}
			}
		}
#endif //DESERIALIZE_SOFT_BODIES

	}
		
	renderme(); 

	glFlush();

	swapBuffers();

}