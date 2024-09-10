void SampleCollision::setup()
{

	SetTitleString(getName());
#ifdef __PPCGEKKO__
	SetHelpString("    a: create rigid bodies");
#else	
	SetHelpString("    b: create rigid bodies");
#endif	

	gShadows = false;

	// Create objects in the scene

	if (!InitCooking(gAllocator, &gErrorStream)) 
	{
		printf("\nError: Unable to initialize the cooking library, exiting the sample.\n\n");
		return;
	}

	// Load ASE file
	CookASE("fluidSample.ase", gScene, NxVec3(1,10,0));
	CookASE("coolFlow.ase", gScene, NxVec3(1,6,-0), NxVec3(1,0.2,1));
	CloseCooking();

	// Add a box shaped drain.
	NxActorDesc boxDrainActor;
	NxBoxShapeDesc boxDrainShape;
	boxDrainActor.shapes.pushBack(&boxDrainShape);
	boxDrainShape.dimensions.set(40,1,40);
	boxDrainShape.shapeFlags |= NX_SF_FLUID_DRAIN;
	boxDrainActor.globalPose.t.set(0, 0, 0);
	gScene->createActor(boxDrainActor);

	//Pre cook hotspots
	NxBounds3 precookAABB;
	precookAABB.set(NxVec3(-20,-20,-20), NxVec3(20,20,20));
//	gScene->cookFluidMeshHotspot(precookAABB, PACKET_SIZE_MULTIPLIER, REST_PARTICLES_PER_METER, KERNEL_RADIUS_MULTIPLIER, MOTION_LIMIT_MULTIPLIER, COLLISION_DISTANCE_MULTIPLIER );


	//Create a set of initial particles
	ParticleSDK*	initParticles = new ParticleSDK[MAX_PARTICLES];
	unsigned initParticlesNum = 0;

	NxVec3 fluidPos(0, 11.6, 0);
	float distance = 0.1f;
	unsigned sideNum = 16;	
	float rad = sideNum*distance*0.5f;
	for (unsigned i=0; i<sideNum; i++)
		for (unsigned j=0; j<sideNum; j++)
			for (unsigned k=0; k<sideNum; k++)
			{
				NxVec3 p = NxVec3(i*distance,j*distance,k*distance);
				if (p.distance(NxVec3(rad,rad,rad)) < rad)
				{
					p += fluidPos;
					ParticleSDK& newParticle = initParticles[initParticlesNum++];
					newParticle.position = p;
					newParticle.velocity = NxVec3(0,0,0);
				}
			}
	//Setup structure to pass initial particles.
	NxParticleData initParticleData;
	initParticleData.numParticlesPtr		= &initParticlesNum;
	initParticleData.bufferPos				= &initParticles[0].position.x;
	initParticleData.bufferPosByteStride	= sizeof(ParticleSDK);
	initParticleData.bufferVel				= &initParticles[0].velocity.x;
	initParticleData.bufferVelByteStride	= sizeof(ParticleSDK);

	//Setup fluid descriptor
	NxFluidDesc fluidDesc;
	fluidDesc.maxParticles                  	= initParticlesNum;
	fluidDesc.kernelRadiusMultiplier			= KERNEL_RADIUS_MULTIPLIER;
	fluidDesc.restParticlesPerMeter				= REST_PARTICLES_PER_METER;
	fluidDesc.collisionDistanceMultiplier   	= COLLISION_DISTANCE_MULTIPLIER;
	fluidDesc.stiffness							= 50.0f;
	fluidDesc.viscosity							= 22.0f;
	fluidDesc.damping							= 0.0f;
	fluidDesc.restitutionForStaticShapes		= 0.4f;
	fluidDesc.dynamicFrictionForStaticShapes	= 0.03f;
	fluidDesc.simulationMethod					= NX_F_SPH; //NX_F_NO_PARTICLE_INTERACTION;

	if (!gHardwareSimulation)
		fluidDesc.flags &= ~NX_FF_HARDWARE;

	fluidDesc.initialParticleData			= initParticleData;

	//Create user fluid.
	//- create NxFluid in NxScene
	//- setup the buffers to read from data from the SDK
	//- set NxFluid::userData field to MyFluid instance
	bool trackUserData = false;
	bool provideCollisionNormals = false;
	MyFluid* fluid = new MyFluid(gScene, fluidDesc, trackUserData, provideCollisionNormals, NxVec3(0.2f,0.3f,0.7f), 0.03f);
	assert(fluid);
	gMyFluids.pushBack(fluid);

	delete[] initParticles;

	gCameraPos.set(23, 14, 23);
	gCameraForward = fluidPos - NxVec3(0, 3, 0) - gCameraPos;
	gCameraForward.normalize();

}