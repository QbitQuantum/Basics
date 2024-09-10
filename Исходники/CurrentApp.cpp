void CurrentApp::Update(float dt)
{
	//Update the camera for movement
	m_camera->Update(dt);
	m_particleEmitter->update(dt);

	glm::vec3 pos = glm::vec3(100 * cos(CurrentTime() * 0.05f) + 150, 80, 100 * sin(CurrentTime() * 0.05f) + 150);
	m_fairyEmitter->SetPosition(pos);
	m_light->SetPosition(pos);

	for (int i = 0; i < 5; ++i)
	{
		m_AI[i]->update(dt);
	}

	Input* IM = Input::GetInstance();

	glm::mat4 cameraWorld = m_camera->GetTransform();
	PxVec3 displacement = PxVec3(0, 0, 0);
	bool notZero = false;
	bool m_canFly = false;

	if (IM->IsKeyDown('W'))
	{
		displacement -= PxVec3(cameraWorld[2].x, (m_canFly ? cameraWorld[2].y : 0), cameraWorld[2].z);
		notZero = true;
	}
	if (IM->IsKeyDown('A'))
	{
		displacement -= PxVec3(cameraWorld[0].x, (m_canFly ? cameraWorld[0].y : 0), cameraWorld[0].z);
		notZero = true;
	}
	if (IM->IsKeyDown('S'))
	{
		displacement += PxVec3(cameraWorld[2].x, (m_canFly ? cameraWorld[2].y : 0), cameraWorld[2].z);
		notZero = true;
	}
	if (IM->IsKeyDown('D'))
	{
		displacement += PxVec3(cameraWorld[0].x, (m_canFly ? cameraWorld[0].y : 0), cameraWorld[0].z);
		notZero = true;
	}

	if (notZero)
		displacement = displacement.getNormalized();

	if (m_verticleSpeed > -10.0f && !m_canFly || m_verticleSpeed > 0 && m_canFly)
		m_verticleSpeed -= dt;

	displacement.y += m_verticleSpeed;

	PxControllerFilters filters;
	g_PlayerController->move(displacement, 0.01f, dt, filters);

	PxExtendedVec3 playerPos = g_PlayerController->getPosition();
	PxExtendedVec3 footPos = g_PlayerController->getFootPosition();
	//I do these calculations individually inside this vector constructor because PxEtendedVec3 doesn't contain some of the necessary operators to do this.
	vec3 endPos = vec3(2.0f * playerPos.x - footPos.x, 2.0f * playerPos.y - footPos.y, 2.0f * playerPos.z - footPos.z);
	m_camera->SetPosition(endPos);

	//Freeze the physics
	if (m_freezePhysics == false) 
	{ 
		UpdatePhysx(dt); 
	}
	else 
	{ 
		UpdatePhysx(0); 
	}

	//Generate new map
	if (Input::GetInstance()->IsKeyPressed('R'))
	{
		m_terrain->GenerateFromPerlin();
		m_terrain->AddPhysicsShape(g_PhysicsScene, g_Physics);
		m_nodeMap->GenerateFromTerrain(m_terrain);
		m_world->Generate();

		for (unsigned int i = 0; i < g_PhysXActors.size(); ++i)
		{
			PxTransform transform(PxVec3(150, 5 + (1.1f * i), 150));
			g_PhysXActors[i]->setGlobalPose(transform);
		}
	}

	if (Input::GetInstance()->IsKeyPressed('N'))
	{
		m_nodeMap->GenerateFromTerrain(m_terrain);
		m_nodeMap->Draw();
	}

	//Freeze Physics
	if (Input::GetInstance()->IsKeyPressed(GLFW_KEY_PAUSE)) { m_freezePhysics = !m_freezePhysics; }

	//Hide/Show Cursor
	if (Input::GetInstance()->IsKeyPressed(KEY_ESCAPE)) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
	if (Input::GetInstance()->IsMousePressed(MOUSE_BUTTON_LEFT)) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }

	//Deffered/Forward
	if (Input::GetInstance()->IsKeyPressed(KEY_F5)) { m_isDeffered = !m_isDeffered; }
	if (Input::GetInstance()->IsKeyPressed(KEY_F6)) { m_drawDebug = !m_drawDebug; }
}