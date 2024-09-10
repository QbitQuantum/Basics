void NpCloth::visualize(Cm::RenderOutput& out, NpScene* scene)
{
	PxClothParticleData* readData = lockParticleData();
	if (!readData)
		return;

	NpClothFabric* fabric = static_cast<NpClothFabric*> (getFabric());

	PxU32 nbSets = fabric->getNbSets();
	PxU32 nbPhases = fabric->getNbPhases();
	PxU32 nbIndices = fabric->getNbParticleIndices();

	shdfnd::Array<PxU32> sets(nbSets);
	shdfnd::Array<PxClothFabricPhase> phases(nbPhases);
	shdfnd::Array<PxU32> indices(nbIndices);

	fabric->getSets(&sets[0], nbSets);
	fabric->getPhases(&phases[0], nbPhases);
	fabric->getParticleIndices(&indices[0], nbIndices);

	const PxU32 lineColor[] = 
	{	
		PxU32(PxDebugColor::eARGB_RED),
		PxU32(PxDebugColor::eARGB_GREEN),
		PxU32(PxDebugColor::eARGB_BLUE),
		PxU32(PxDebugColor::eARGB_YELLOW),
		PxU32(PxDebugColor::eARGB_MAGENTA)
	};

	PxU32 colorIndex = 0;

	const PxClothParticle* particles = readData->particles;
	const PxTransform xform = getGlobalPose();

	out << Cm::RenderOutput::LINES;

	for (PxU32 p=0; p < nbPhases; ++p)
	{
		PxClothFabricPhaseType::Enum phaseType = fabric->getPhaseType(p);

		float scale = 0.0f;

		// check if visualization requested
		switch(phaseType)
		{
		case PxClothFabricPhaseType::eVERTICAL:
			scale = scene->getVisualizationParameter(PxVisualizationParameter::eCLOTH_VERTICAL);
			break;
		case PxClothFabricPhaseType::eHORIZONTAL:
			scale = scene->getVisualizationParameter(PxVisualizationParameter::eCLOTH_HORIZONTAL);
			break;
		case PxClothFabricPhaseType::eBENDING:
			scale = scene->getVisualizationParameter(PxVisualizationParameter::eCLOTH_BENDING);
			break;
		case PxClothFabricPhaseType::eSHEARING:
			scale = scene->getVisualizationParameter(PxVisualizationParameter::eCLOTH_SHEARING);
			break;
		case PxClothFabricPhaseType::eINVALID:
		case PxClothFabricPhaseType::eCOUNT:
			break;
		}

		if (scale == 0.0f)
			continue;

		out << lineColor[colorIndex];

		PxU32 set = phases[p].setIndex;

		// draw one set at a time
		PxU32 iIt = set ? 2*sets[set-1] : 0;
		PxU32 iEnd = 2*sets[set]; 

		// iterate over constraints
		while (iIt < iEnd)
		{
			PxU32 i0 = indices[iIt++];
			PxU32 i1 = indices[iIt++];

			// ideally we would know the mesh normals here and bias off
			// the surface slightly but scaling slightly around the center helps
			out << xform.transform(particles[i0].pos);
			out << xform.transform(particles[i1].pos);
		}

		colorIndex = (colorIndex+1)%5;
	}

	// draw virtual particles
	if (scene->getVisualizationParameter(PxVisualizationParameter::eCLOTH_VIRTUAL_PARTICLES) > 0.0f)
	{
		PxU32 nbVirtualParticles = getNbVirtualParticles();

		if (nbVirtualParticles)
		{
			out << Cm::RenderOutput::POINTS;
			out << PxU32(PxDebugColor::eARGB_WHITE);

			shdfnd::Array<PxU32> vpIndices(nbVirtualParticles*4);
			getVirtualParticles(&vpIndices[0]);

			// get weights table
			PxU32 nbVirtualParticleWeights = getNbVirtualParticleWeights();
			shdfnd::Array<PxVec3> vpWeights(nbVirtualParticleWeights);
			getVirtualParticleWeights(&vpWeights[0]);

			for (PxU32 i=0; i < nbVirtualParticles; ++i)
			{
				PxU32 i0 = vpIndices[i*4+0];
				PxU32 i1 = vpIndices[i*4+1];
				PxU32 i2 = vpIndices[i*4+2];

				PxVec3 v0 = xform.transform(readData->particles[i0].pos);
				PxVec3 v1 = xform.transform(readData->particles[i1].pos);
				PxVec3 v2 = xform.transform(readData->particles[i2].pos);

				PxVec3 weights = vpWeights[vpIndices[i*4+3]];

				out << (v0*weights.x + v1*weights.y + v2*weights.z);
			}
		}
	}

	readData->unlock();
}