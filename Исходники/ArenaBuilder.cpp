void ArenaBuilder::GenerateProbendingArena(IScene* scene)
{
	using namespace physx;

#pragma region Water
	///Create the water plane
	SharedGameObject waterObject = std::make_shared<GameObject>(scene, "WaterPlane");
	MeshRenderComponent* waterMesh = new MeshRenderComponent();
	waterObject->AttachComponent(waterMesh);
	waterMesh->LoadModel("BasicPlane");
	waterMesh->SetMaterial("Examples/Water1");
	RigidBodyComponent* waterRigid = new RigidBodyComponent();
	
	waterObject->AttachComponent(waterRigid);
	Ogre::Quaternion rot = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0f)), Ogre::Vector3(0, 0, 1));
	waterRigid->CreateRigidBody(RigidBodyComponent::STATIC);//, physx::PxVec3(0.0f, -5.0f, 0.0f), physx::PxQuat(rot.x, rot.y, rot.z, rot.w));
	waterRigid->AttachShape("BasicPlane");
	//waterRigid->CreateDebugDraw();

	waterObject->SetWorldTransform(Ogre::Vector3(0.0f, -5.0f, 0.0f), rot, Ogre::Vector3(50.0f, 50.0f, 50.0f));
	waterObject->Start();

	scene->AddGameObject(waterObject);

#pragma endregion

#pragma region ArenaSurface
	SharedGameObject arenaSurface = std::make_shared<GameObject>(scene, "ProbendArenaSurface");
	MeshRenderComponent* arenaSurfaceMesh = new MeshRenderComponent();
	arenaSurface->AttachComponent(arenaSurfaceMesh);
	arenaSurfaceMesh->LoadModel("ProbendArenaSurface.mesh");

	RigidBodyComponent* arenaSurfaceRigid = new RigidBodyComponent();
	arenaSurface->AttachComponent(arenaSurfaceRigid);
	arenaSurfaceRigid->CreateRigidBody(RigidBodyComponent::STATIC);
	arenaSurfaceRigid->AttachShape("ArenaSurfaceShape");
	arenaSurfaceRigid->CreateDebugDraw();

	arenaSurface->Start();
	scene->AddGameObject(arenaSurface);

#pragma endregion

#pragma region Pillars
	//////////////////////PILLARS//////////////////////

	//RL indicates Red Left from Red perspective
	SharedGameObject arenaPillarRL = std::make_shared<GameObject>(scene, "ProbendPillarRL");
	MeshRenderComponent* arenaPillarMesh = new MeshRenderComponent();
	arenaPillarRL->AttachComponent(arenaPillarMesh);
	arenaPillarMesh->LoadModel("ProbendPillar.mesh");

	RigidBodyComponent* arenaPillarRigid = new RigidBodyComponent();
	arenaPillarRL->AttachComponent(arenaPillarRigid);
	arenaPillarRigid->CreateRigidBody(RigidBodyComponent::STATIC);

	arenaPillarRigid->AttachShape("ArenaPillarShape");
	arenaPillarRigid->CreateDebugDraw();

	//Set transform as calculated by Ogitor
	arenaPillarRL->SetWorldTransform(Ogre::Vector3(5.9f, -2.85f, 2.15f), 
		Ogre::Quaternion(0.0f, -0.254602f, 0.0f, 0.967046f), Ogre::Vector3(1.0f));

	arenaPillarRL->Start();
	scene->AddGameObject(arenaPillarRL);

	SharedGameObject arenaPillarRR = arenaPillarRL->Clone(); 
	arenaPillarRR->SetWorldTransform(Ogre::Vector3(5.9f, -2.85f, -2.15f), 
		Ogre::Quaternion(0.0f, 0.258819f, 0.0f, 0.967046f), Ogre::Vector3(1.0f));

	arenaPillarRR->Start();
	scene->AddGameObject(arenaPillarRR);

	SharedGameObject arenaPillarCR = arenaPillarRL->Clone();
	arenaPillarCR->SetWorldTransform(Ogre::Vector3(0.0f, -2.85f, -4.3f), 
		Ogre::Quaternion(0.0f, -0.700909f, 0.0f, 0.71325f), Ogre::Vector3(1.0f));

	arenaPillarCR->Start();
	scene->AddGameObject(arenaPillarCR);

	SharedGameObject arenaPillarCL = arenaPillarRL->Clone();
	arenaPillarCL->SetWorldTransform(Ogre::Vector3(0.0f, -2.85f, 4.3f), 
		Ogre::Quaternion(0.0f, -0.700909f, 0.0f, 0.71325f), Ogre::Vector3(1.0f));

	arenaPillarCL->Start();
	scene->AddGameObject(arenaPillarCL);

	SharedGameObject arenaPillarBR = arenaPillarRL->Clone();
	arenaPillarBR->SetWorldTransform(Ogre::Vector3(-5.9f, -2.85f, -2.15f), 
		Ogre::Quaternion(0.0f, -0.258819f, 0.0f, 0.965926f), Ogre::Vector3(1.0f));

	arenaPillarBR->Start();
	scene->AddGameObject(arenaPillarBR);

	SharedGameObject arenaPillarBL = arenaPillarRL->Clone();
	arenaPillarBL->SetWorldTransform(Ogre::Vector3(-5.9f, -2.85f, 2.15f), 
		Ogre::Quaternion(0.0f, 0.258819f, 0.0f, 0.965926f), Ogre::Vector3(1.0f));

	arenaPillarBL->Start();
	scene->AddGameObject(arenaPillarBL);

	///////////////////END PILLARS///////////////////
#pragma endregion

#pragma region Walls
	
	SharedGameObject leftWall = std::make_shared<GameObject>(scene, "Wall");
	MeshRenderComponent* wallMesh = new MeshRenderComponent();
	leftWall->AttachComponent(wallMesh);
	wallMesh->LoadModel("BasicPlane");
	wallMesh->SetMaterial("StadiumWall");
	Ogre::Radian ninetyDeg = Ogre::Radian(Ogre::Degree(90.0f));
	Ogre::Quaternion leftWallRot = Ogre::Quaternion(ninetyDeg, Ogre::Vector3::UNIT_Y);
	RigidBodyComponent* wallRigid = new RigidBodyComponent();
	leftWall->AttachComponent(wallRigid);
	wallRigid->CreateRigidBody(RigidBodyComponent::STATIC);
	wallRigid->AttachShape("ArenaWallShape1");
	wallRigid->CreateDebugDraw();
	leftWall->SetWorldTransform(Ogre::Vector3(0.0f, 0.0f, 20.0f),leftWallRot, Ogre::Vector3(10.0f, 10.0f, 7.5f));

	leftWall->Start();
	scene->AddGameObject(leftWall);

#pragma endregion
}