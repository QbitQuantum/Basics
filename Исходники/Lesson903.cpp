NxFluid* CreateFluid(const NxVec3& pos, NxU32 sideNum, NxReal distance, NxScene* scene)
{
	float rad = sideNum*distance*0.5;
	for (unsigned i=0; i<sideNum; i++)
		for (unsigned j=0; j<sideNum; j++)
			for (unsigned k=0; k<sideNum; k++)
			{
				NxVec3 p = NxVec3(i*distance,j*distance,k*distance);
				if (p.distance(NxVec3(rad,rad,rad)) < rad)
				{
					p += pos;
					if(gParticleBufferNum< MAX_PARTICLES)
						gParticleBuffer[gParticleBufferNum++] = p;
				}
			}

	NxParticleData particles;

	//particles.maxParticles			= gParticleBufferCap;
	particles.numParticlesPtr		= &gParticleBufferNum;
	particles.bufferPos				= &gParticleBuffer[0].x;
	particles.bufferPosByteStride	= sizeof(NxVec3);

	//Create a fluid descriptor
	NxFluidDesc fluidDesc;
	fluidDesc.maxParticles = MAX_PARTICLES;
	fluidDesc.flags |= NX_FF_COLLISION_TWOWAY;
	fluidDesc.simulationMethod	= NX_F_SPH;
	fluidDesc.restParticlesPerMeter			= 5.0f;
	fluidDesc.motionLimitMultiplier			= 10.0f;
	fluidDesc.restDensity					= 1000.0f;
	fluidDesc.kernelRadiusMultiplier		= 1.6f;
	fluidDesc.stiffness						= 10.0f;
	fluidDesc.viscosity						= 50.0f;
	fluidDesc.damping						= 0.5f;
	fluidDesc.packetSizeMultiplier			= 16;
	fluidDesc.name                          = "fluid";

	fluidDesc.kernelRadiusMultiplier		= KERNEL_RADIUS_MULTIPLIER;
	fluidDesc.restParticlesPerMeter			= REST_PARTICLES_PER_METER;
	fluidDesc.motionLimitMultiplier			= MOTION_LIMIT_MULTIPLIER;
	fluidDesc.packetSizeMultiplier			= PACKET_SIZE_MULTIPLIER;
	fluidDesc.stiffness						= 40;  // 50
	fluidDesc.viscosity						= 22;
	fluidDesc.restDensity					= 1000;
	fluidDesc.damping						= 0;
// There are some API changes since 280 version, Fluid collision coefficients have been renamed, 
// E.g. NxFluidDesc::dynamicCollisionAdhesion is named NxFluidDesc::dynamicFrictionForDynamicShapes. 
#if NX_SDK_VERSION_NUMBER < 280
	fluidDesc.staticCollisionRestitution = 0.162f;
	fluidDesc.staticCollisionAdhesion = 0.146f;
	fluidDesc.dynamicCollisionRestitution = 0.5f;
	fluidDesc.dynamicCollisionAdhesion = 0.5f;
#else 
	fluidDesc.restitutionForStaticShapes = 0.162f;
	fluidDesc.dynamicFrictionForStaticShapes  = 0.146f;
	fluidDesc.restitutionForDynamicShapes = 0.5f;
	fluidDesc.dynamicFrictionForDynamicShapes = 0.5f;
#endif
	fluidDesc.simulationMethod				= NX_F_SPH;  //NX_F_NO_PARTICLE_INTERACTION;

	fluidDesc.initialParticleData			= particles;
	fluidDesc.particlesWriteData			= particles;

	if(!bHardwareFluid)
		fluidDesc.flags &= ~NX_FF_HARDWARE;

    fluid = gScene->createFluid(fluidDesc);
	if(!fluid)
	{
		fluidDesc.flags &= ~NX_FF_HARDWARE;
		bHardwareFluid = false;
		fluid = gScene->createFluid(fluidDesc);
	}
	
	assert(fluid != NULL);
	return fluid;
}