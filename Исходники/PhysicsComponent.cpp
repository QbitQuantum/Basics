void PhysicsComponent::loadFromXml(const XMLNode* description) {
	GameLog::logMessage("LOADING BULLET FROM XML");
	// Delete old physics representation
	//release();

	Matrix4f objTrans;
	m_owner->executeEvent(&GameEvent(GameEvent::E_TRANSFORMATION, &GameEventData((float*) objTrans.x, 16), this));

	Vec3f t, r, s;
	objTrans.decompose(t, r, s);

	// Parse Physics Node Configuration
	float mass = static_cast<float>(atof(description->getAttribute("mass", "0.0")));

	const char* shape = description->getAttribute("shape", "Box");
	// create collision shape based on the node configuration
	if (shape && _stricmp(shape, "Box") == 0) // Bounding Box Shape
			{
		float dimX = static_cast<float>(atof(description->getAttribute("x", "1.0")));
		float dimY = static_cast<float>(atof(description->getAttribute("y", "1.0")));
		float dimZ = static_cast<float>(atof(description->getAttribute("z", "1.0")));
		// update box settings with node scaling (TODO is this necessary if we already set the scale by using setLocalScaling?)
		//m_collisionShape = new btBoxShape(btVector3(dimX * s.x, dimY * s.y, dimZ * s.z));
		m_collisionShape = new btBoxShape(btVector3(dimX, dimY, dimZ));
	} else if (shape && _stricmp(shape, "Sphere") == 0) // Sphere Shape
			{
		float radius = static_cast<float>(atof(description->getAttribute("radius", "1.0")));
		m_collisionShape = new btSphereShape(radius);
	} else if (shape && _stricmp(shape, "Cylinder") == 0) // Cylinder Shape
			{
		float radius0 = static_cast<float>(atof(description->getAttribute("radius", "1.0")));
		float height = static_cast<float>(atof(description->getAttribute("height", "1.0")));
		m_collisionShape = new btCylinderShape(btVector3(radius0, height, radius0));
	} else // Mesh Shape
	{
		MeshData meshData;
		GameEvent meshEvent(GameEvent::E_MESH_DATA, &meshData, this);
		// get mesh data from graphics engine
		m_owner->executeEvent(&meshEvent);

		if (meshData.VertexBase && (meshData.TriangleBase32 || meshData.TriangleBase16)) {
			// Create new mesh in physics engine
			m_btTriangleMesh = new btTriangleMesh();
			int offset = 3;
			if (meshData.TriangleMode == 5) // Triangle Strip
				offset = 1;

			// copy mesh from graphics to physics
			bool index16 = false;
			if (meshData.TriangleBase16)
				index16 = true;
			for (unsigned int i = 0; i < meshData.NumTriangleIndices - 2; i += offset) {
				unsigned int index1 = index16 ? (meshData.TriangleBase16[i] - meshData.VertRStart) * 3 : (meshData.TriangleBase32[i] - meshData.VertRStart) * 3;
				unsigned int index2 = index16 ? (meshData.TriangleBase16[i + 1] - meshData.VertRStart) * 3 : (meshData.TriangleBase32[i + 1] - meshData.VertRStart) * 3;
				unsigned int index3 = index16 ? (meshData.TriangleBase16[i + 2] - meshData.VertRStart) * 3 : (meshData.TriangleBase32[i + 2] - meshData.VertRStart) * 3;
				m_btTriangleMesh->addTriangle(btVector3(meshData.VertexBase[index1], meshData.VertexBase[index1 + 1], meshData.VertexBase[index1 + 2]),
						btVector3(meshData.VertexBase[index2], meshData.VertexBase[index2 + 1], meshData.VertexBase[index2 + 2]),
						btVector3(meshData.VertexBase[index3], meshData.VertexBase[index3 + 1], meshData.VertexBase[index3 + 2]));
			}

			bool useQuantizedAabbCompression = true;

			if (mass > 0) {
				//btGImpactMeshShape* shape = new btGImpactMeshShape(m_btTriangleMesh);

				btGImpactConvexDecompositionShape* shape = new btGImpactConvexDecompositionShape(m_btTriangleMesh, btVector3(1.f, 1.f, 1.f), btScalar(0.1f), true);

				shape->updateBound();

				//btCollisionDispatcher* dispatcher = static_cast<btCollisionDispatcher *>(Physics::instance()->dispatcher());
				//btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);

				m_collisionShape = shape;

				//m_collisionShape = new btConvexTriangleMeshShape(m_btTriangleMesh);
			} else
				// BvhTriangleMesh can be used only for static objects
				m_collisionShape = new btBvhTriangleMeshShape(m_btTriangleMesh, useQuantizedAabbCompression);
		} else {
			GameLog::errorMessage("The mesh data for the physics representation couldn't be retrieved");
			return;
		}
	}

	GameLog::logMessage("PARSED SHAPE FROM XML");

	bool kinematic = _stricmp(description->getAttribute("kinematic", "false"), "true") == 0 || _stricmp(description->getAttribute("kinematic", "0"), "1") == 0;

	bool nondynamic = _stricmp(description->getAttribute("static", "false"), "true") == 0 || _stricmp(description->getAttribute("static", "0"), "1") == 0;

	bool ragdoll = _stricmp(description->getAttribute("ragdoll", "false"), "true") == 0 || _stricmp(description->getAttribute("ragdoll", "0"), "1") == 0;
	// Create initial transformation without scale
	btTransform tr;
	tr.setIdentity();
	tr.setRotation(btQuaternion(r.x, r.y, r.z));

	btMatrix3x3 rot = tr.getBasis();

	XMLNode offsetXMLNode = description->getChildNode("Offset");

	if (!offsetXMLNode.isEmpty()) {
		lX = static_cast<float>(atof(offsetXMLNode.getAttribute("lX", "0.0")));
		lY = static_cast<float>(atof(offsetXMLNode.getAttribute("lY", "0.0")));
		lZ = static_cast<float>(atof(offsetXMLNode.getAttribute("lZ", "0.0")));
	}

	btVector3 offset = btVector3(lX * s.x, lY * s.y, lZ * s.z);

	tr.setOrigin(btVector3(t.x, t.y, t.z) + rot * offset);
	// Set local scaling in collision shape because Bullet does not support scaling in the world transformation matrices
	m_collisionShape->setLocalScaling(btVector3(s.x, s.y, s.z));
	btVector3 localInertia(0, 0, 0);
	//rigidbody is dynamic if and only if mass is non zero otherwise static
	if (mass != 0)
		m_collisionShape->calculateLocalInertia(mass, localInertia);
	if (mass != 0 || kinematic)
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_motionState = new btDefaultMotionState(tr);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_motionState, m_collisionShape, localInertia);
	rbInfo.m_startWorldTransform = tr;
	//rbInfo.m_restitution = btScalar( atof(description->getAttribute("restitution", "0")) );
	//rbInfo.m_friction = btScalar( atof(description->getAttribute("static_friction", "0.5")) );
	// Threshold for deactivation of objects (if movement is below this value the object gets deactivated)
	//rbInfo.m_angularSleepingThreshold = 0.8f;
	//rbInfo.m_linearSleepingThreshold = 0.8f;

	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserPointer(this);
	m_rigidBody->setDeactivationTime(2.0f);

	// Add support for collision detection if mass is zero but kinematic is explicitly enabled
	if (kinematic && mass == 0 && !nondynamic) {
		m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
	}
	if (nondynamic && mass == 0) {
		m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
	}

	bool isTrigger = _stricmp(description->getAttribute("solid", "true"), "false") == 0 || _stricmp(description->getAttribute("solid", "1"), "0") == 0;
	if (isTrigger) {
		setCollisionResponse(true);
	}

	GameLog::logMessage("I'm a new Physics body: %s my Motion state: %d", m_owner->id().c_str(), m_motionState);
	printf("I'm a new Physics body: %s my Motion state: %d\n", m_owner->id().c_str(), m_motionState);

	if(!ragdoll) Physics::instance()->addObject(this);

	/*Geometry Proxy*/
	XMLNode proxyXMLNode = description->getChildNode("Proxy");
	if (proxyXMLNode.isEmpty())
		return;

	m_proxy = GameModules::gameWorld()->entity(proxyXMLNode.getAttribute("name", ""));

	if (m_proxy) {
		m_proxy->addListener(GameEvent::E_SET_TRANSFORMATION, this);
		m_proxy->addListener(GameEvent::E_SET_TRANSLATION, this);
		m_proxy->addListener(GameEvent::E_SET_ROTATION, this);
		m_proxy->addListener(GameEvent::E_TRANSLATE_LOCAL, this);
		m_proxy->addListener(GameEvent::E_TRANSLATE_GLOBAL, this);
		m_proxy->addListener(GameEvent::E_ROTATE_LOCAL, this);
	} else
		printf("No PROXY FOUND with EntityID: %s\n", proxyXMLNode.getAttribute("name", ""));

	/*Adding constraints*/

	XMLNode constraintXMLNode = description->getChildNode("Constraint");
	if (constraintXMLNode.isEmpty())
		return;

	const char* constraintType = constraintXMLNode.getAttribute("type", "Hinge");
	const char* parentName = constraintXMLNode.getAttribute("parent", "");
	PhysicsComponent* parent = getParent(parentName);

	if (!parent) {
		printf("NO PARENT FOUND\n");
		return;
	}

	XMLNode transformXMLNode = constraintXMLNode.getChildNode("TransformA");
	float qX = static_cast<float>(atof(transformXMLNode.getAttribute("qx", "1.0")));
	float qY = static_cast<float>(atof(transformXMLNode.getAttribute("qy", "1.0")));
	float qZ = static_cast<float>(atof(transformXMLNode.getAttribute("qz", "1.0")));
	float qW = static_cast<float>(atof(transformXMLNode.getAttribute("qw", "1.0")));
	float vX = static_cast<float>(atof(transformXMLNode.getAttribute("vx", "1.0")));
	float vY = static_cast<float>(atof(transformXMLNode.getAttribute("vy", "1.0")));
	float vZ = static_cast<float>(atof(transformXMLNode.getAttribute("vz", "1.0")));
	btTransform transformA;
	transformA.setIdentity();
	printf("%f \t %f \t %f  \n ", qX, qY, qZ);
	transformA.getBasis().setEulerZYX(qZ, qY, qX);
//	transformA.getBasis().setEulerZYX(M_PI_2,0,0);
	transformA.setOrigin(btVector3(vX * s.x, vY * s.y, vZ * s.z));
//	printf("%f \t %f \t %f \t %s \n ", vX*s.x, vY*s.y, vZ*s.z, m_owner ? m_owner->id().c_str() : "no name");
//	btTransform transformA = btTransform(btQuaternion(qX, qY, qZ, qW), btVector3(vX*s.x, vY*s.y, vZ*s.z));

	transformXMLNode = constraintXMLNode.getChildNode("TransformB");
	qX = static_cast<float>(atof(transformXMLNode.getAttribute("qx", "1.0")));
	qY = static_cast<float>(atof(transformXMLNode.getAttribute("qy", "1.0")));
	qZ = static_cast<float>(atof(transformXMLNode.getAttribute("qz", "1.0")));
	qW = static_cast<float>(atof(transformXMLNode.getAttribute("qw", "1.0")));
	vX = static_cast<float>(atof(transformXMLNode.getAttribute("vx", "1.0")));
	vY = static_cast<float>(atof(transformXMLNode.getAttribute("vy", "1.0")));
	vZ = static_cast<float>(atof(transformXMLNode.getAttribute("vz", "1.0")));
//	btTransform transformB = btTransform(btQuaternion(qX, qY, qZ, qW), btVector3(vX*s.x, vY*s.y, vZ*s.z));
	btTransform transformB;
	transformB.setIdentity();
	transformB.getBasis().setEulerZYX(qZ, qY, qX);
//	transformB.getBasis().setEulerZYX(M_PI_2,0,0);
	transformB.setOrigin(btVector3(vX * s.x, vY * s.y, vZ * s.z));

	XMLNode limitXMLNode = constraintXMLNode.getChildNode("Limit");

	if (_stricmp(constraintType, "Hinge") == 0) {
		btHingeConstraint* parentConstraint = new btHingeConstraint(*(parent->rigidBody()), *m_rigidBody, transformA, transformB);
		float low = static_cast<float>(atof(limitXMLNode.getAttribute("low", "0.0")));
		float high = static_cast<float>(atof(limitXMLNode.getAttribute("high", "0.75")));
		float softness = static_cast<float>(atof(limitXMLNode.getAttribute("softness", "0.9")));
		float biasFactor = static_cast<float>(atof(limitXMLNode.getAttribute("biasFactor", "0.3")));
		float relaxationFactor = static_cast<float>(atof(limitXMLNode.getAttribute("relaxationFactor", "1.0")));

		parentConstraint->setLimit(low, high, softness, biasFactor, relaxationFactor);
		m_parentConstraint = parentConstraint;
	} else if (_stricmp(constraintType, "ConeTwist") == 0) {
		btConeTwistConstraint* parentConstraint = new btConeTwistConstraint(*(parent->rigidBody()), *m_rigidBody, transformA, transformB);
		float swingSpan1 = static_cast<float>(atof(limitXMLNode.getAttribute("swingSpan1", "1.0")));
		float swingSpan2 = static_cast<float>(atof(limitXMLNode.getAttribute("swingSpan2", "1.0")));
		float twistSpan = static_cast<float>(atof(limitXMLNode.getAttribute("twistSpan", "1.0")));
		float softness = static_cast<float>(atof(limitXMLNode.getAttribute("softness", "0.9")));
		float biasFactor = static_cast<float>(atof(limitXMLNode.getAttribute("biasFactor", "0.3")));
		float relaxationFactor = static_cast<float>(atof(limitXMLNode.getAttribute("relaxationFactor", "1.0")));

		parentConstraint->setLimit(swingSpan1, swingSpan2, twistSpan, softness, biasFactor, relaxationFactor);
		m_parentConstraint = parentConstraint;
	}

	if(!ragdoll) Physics::instance()->addConstraint(m_parentConstraint);

}