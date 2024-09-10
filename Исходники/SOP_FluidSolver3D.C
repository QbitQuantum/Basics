OP_ERROR SOP_FluidSolver3D::cookMySop(OP_Context &context) {

	oldf = f;
	f =	context.getFrame();

	double t = context.getTime();

	fluidSolver->fps = OPgetDirector()->getChannelManager()->getSamplesPerSec();

	UT_Interrupt	*boss;
	GU_PrimVolume	*volume;
	GU_PrimVolume	*velXVolume;
	GU_PrimVolume	*velYVolume;
	GU_PrimVolume	*velZVolume;

	OP_Node::flags().timeDep = 1;

	int newResX = RESX(t);
	int newResY = RESY(t);
	int newResZ = RESZ(t);

	if ( newResX != fluidSolver->res.width || newResY != fluidSolver->res.height || newResZ != fluidSolver->res.depth) {
		fluidSolver->changeFluidRes(newResX,newResY,newResZ);

	}

	UT_Vector3 fluidPos(POSX(t), POSY(t), POSZ(t));
	UT_Vector3 fluidRot(ROTX(t), ROTY(t), ROTZ(t));
	fluidRot.degToRad();

	fluidSolver->fluidSize.x = FLUIDSIZEX(t);
	fluidSolver->fluidSize.y = FLUIDSIZEY(t);
	fluidSolver->fluidSize.z = FLUIDSIZEZ(t);

	fluidSolver->borderNegX = BORDERNEGX(t);
	fluidSolver->borderPosX = BORDERPOSX(t);
	fluidSolver->borderNegY = BORDERNEGY(t);
	fluidSolver->borderPosY = BORDERPOSY(t);
	fluidSolver->borderNegZ = BORDERNEGZ(t);
	fluidSolver->borderPosZ = BORDERPOSZ(t);

	fluidSolver->substeps = SUBSTEPS(t);
	fluidSolver->jacIter = JACITER(t);

	fluidSolver->densDis = DENSDIS(t);
	fluidSolver->densBuoyStrength = DENSBUOYSTRENGTH(t);
	float ddirX = DENSBUOYDIRX(t);
	float ddirY = DENSBUOYDIRY(t);
	float ddirZ = DENSBUOYDIRZ(t);
	fluidSolver->densBuoyDir = cu::make_float3(ddirX,ddirY,ddirZ);

	fluidSolver->velDamp = VELDAMP(t);
	fluidSolver->vortConf = VORTCONF(t);

	fluidSolver->noiseStr = NOISESTR(t);
	fluidSolver->noiseFreq = NOISEFREQ(t);
	fluidSolver->noiseOct = NOISEOCT(t);
	fluidSolver->noiseLacun = NOISELACUN(t);
	fluidSolver->noiseSpeed = NOISESPEED(t);
	fluidSolver->noiseAmp = NOISEAMP(t);

	fluidSolver->preview = PREVIEW(t);
	fluidSolver->drawCube = DRAWCUBE(t);
	fluidSolver->opaScale = OPASCALE(t);
	fluidSolver->stepMul = STEPMUL(t);
	fluidSolver->displayRes = DISPLAYRES(t);


	fluidSolver->doShadows = DOSHADOWS(t);
	float lightPosX = LIGHTPOSX(t);
	float lightPosY = LIGHTPOSY(t);
	float lightPosZ = LIGHTPOSZ(t);
	fluidSolver->lightPos = cu::make_float3(lightPosX,lightPosY,lightPosZ);
	fluidSolver->shadowDens = SHADOWDENS(t);
	fluidSolver->shadowStepMul = SHADOWSTEPMUL(t);
	fluidSolver->shadowThres = SHADOWTHRES(t);

	fluidSolver->displaySlice = DISPLAYSLICE(t);
	fluidSolver->sliceType = SLICETYPE(t);
	fluidSolver->sliceAxis = SLICEAXIS(t);
	fluidSolver->slicePos = SLICEPOS(t);
	fluidSolver->sliceBounds = SLICEBOUNDS(t);


    if (error() < UT_ERROR_ABORT) {
		boss = UTgetInterrupt();

	gdp->clearAndDestroy();		

		// Start the interrupt server
		if (boss->opStart("Building Volume")){

			static float		 zero = 0.0;
			GB_AttributeRef fluidAtt = gdp->addAttrib("cudaFluid3DPreview", sizeof(int), GB_ATTRIB_INT, &zero);
			gdp->attribs().getElement().setValue<int>(fluidAtt, fluidSolver->preview);

			GB_AttributeRef fluidSliceAtt = gdp->addAttrib("sliceDisplay", sizeof(int), GB_ATTRIB_INT, &zero);
			gdp->attribs().getElement().setValue<int>(fluidSliceAtt, fluidSolver->displaySlice);

			GB_AttributeRef solverIdAtt = gdp->addAttrib("solverId", sizeof(int), GB_ATTRIB_INT, &zero);
			gdp->attribs().getElement().setValue<int>(solverIdAtt, fluidSolver->id);

			GEO_AttributeHandle         name_gah;
			int	def = -1;

			gdp->addPrimAttrib("name", sizeof(int), GB_ATTRIB_INDEX, &def);
			name_gah = gdp->getPrimAttribute("name");


			UT_Matrix3              xform;
			const UT_XformOrder volXFormOrder;

			volume = (GU_PrimVolume *)GU_PrimVolume::build(gdp);

			volume->getVertex().getPt()->getPos() = fluidPos;

			xform.identity();
			xform.scale(fluidSolver->fluidSize.x*0.5, fluidSolver->fluidSize.y*0.5, fluidSolver->fluidSize.z*0.5);
			xform.rotate(fluidRot.x(), fluidRot.y(), fluidRot.z(), volXFormOrder);

			volume->setTransform(xform);

			name_gah.setElement(volume);
			name_gah.setString("density");

			velXVolume = (GU_PrimVolume *)GU_PrimVolume::build(gdp);
			velXVolume->getVertex().getPt()->getPos() = fluidPos;
			velXVolume->setTransform(xform);

			name_gah.setElement(velXVolume);
			name_gah.setString("vel.x");

			velYVolume = (GU_PrimVolume *)GU_PrimVolume::build(gdp);
			velYVolume->getVertex().getPt()->getPos() = fluidPos;
			velYVolume->setTransform(xform);

			name_gah.setElement(velYVolume);
			name_gah.setString("vel.y");

			velZVolume = (GU_PrimVolume *)GU_PrimVolume::build(gdp);
			velZVolume->getVertex().getPt()->getPos() = fluidPos;
			velZVolume->setTransform(xform);

			name_gah.setElement(velZVolume);
			name_gah.setString("vel.z");


			xform.identity();
			xform.rotate(fluidRot.x(), fluidRot.y(), fluidRot.z(), volXFormOrder);
			xform.invert();

			if(lockInputs(context) >= UT_ERROR_ABORT)
				return error();

			if(getInput(0)){
				GU_Detail* emittersInput = (GU_Detail*)inputGeo(0, context);
				GEO_PointList emittersList = emittersInput->points();
				int numEmitters = emittersList.entries();

				if (numEmitters != fluidSolver->nEmit) {
					delete fluidSolver->emitters;
					fluidSolver->nEmit = numEmitters;
					fluidSolver->emitters = new VHFluidEmitter[numEmitters];
				}

				GEO_AttributeHandle radAh, amountAh;
				radAh = emittersInput->getPointAttribute("radius");
				amountAh = emittersInput->getPointAttribute("amount");

				for (int i = 0; i < numEmitters; i++) {

					UT_Vector4 emitPos = emittersList[i]->getPos();
					UT_Vector3 emitPos3(emitPos);

					emitPos3 -= fluidPos;
					emitPos3 = emitPos3*xform;

					fluidSolver->emitters[i].posX = emitPos3.x();
					fluidSolver->emitters[i].posY = emitPos3.y();
					fluidSolver->emitters[i].posZ = emitPos3.z();

					radAh.setElement(emittersList[i]);
					amountAh.setElement(emittersList[i]);

					fluidSolver->emitters[i].radius = radAh.getF(0);
					fluidSolver->emitters[i].amount = amountAh.getF(0);
				}
			} else {

				fluidSolver->nEmit = 0;

			}
		

			if(getInput(1)) {
				GU_Detail* collidersInput = (GU_Detail*)inputGeo(1, context);
		
				GEO_PointList collidersList = collidersInput->points();
				int numColliders = collidersList.entries();

				if (numColliders != fluidSolver->nColliders) {
					delete fluidSolver->colliders;
					fluidSolver->nColliders = numColliders;
					fluidSolver->colliders = new VHFluidCollider[numColliders];
				}

				GEO_AttributeHandle colRadAh;
				colRadAh = collidersInput->getPointAttribute("radius");

				for (int i = 0; i < numColliders; i++) {

					UT_Vector4 colPos = collidersList[i]->getPos();
					UT_Vector3 colPos3(colPos);

					colPos3 -= fluidPos;
					colPos3 = colPos3*xform;

					if (f > STARTFRAME(t)) {
						fluidSolver->colliders[i].oldPosX = fluidSolver->colliders[i].posX;
						fluidSolver->colliders[i].oldPosY = fluidSolver->colliders[i].posY;
						fluidSolver->colliders[i].oldPosZ = fluidSolver->colliders[i].posZ;
					} else {
						fluidSolver->colliders[i].oldPosX = colPos3.x();
						fluidSolver->colliders[i].oldPosY = colPos3.y();
						fluidSolver->colliders[i].oldPosZ = colPos3.z();
					}

					fluidSolver->colliders[i].posX = colPos3.x();
					fluidSolver->colliders[i].posY = colPos3.y();
					fluidSolver->colliders[i].posZ = colPos3.z();

					colRadAh.setElement(collidersList[i]);

					fluidSolver->colliders[i].radius = colRadAh.getF(0);
				}

			} else {
				fluidSolver->nColliders = 0;
			}

			unlockInputs();

			if (f <= STARTFRAME(t)) {

				fluidSolver->resetFluid();

				if (COPYDENS(t)) {

					{
						UT_VoxelArrayWriteHandleF	handle = volume->getVoxelWriteHandle();
						handle->constant(0);

						UT_VoxelArrayWriteHandleF	velXHandle = velXVolume->getVoxelWriteHandle();
						velXHandle->constant(0);
						UT_VoxelArrayWriteHandleF	velYHandle = velYVolume->getVoxelWriteHandle();
						velYHandle->constant(0);
						UT_VoxelArrayWriteHandleF	velZHandle = velZVolume->getVoxelWriteHandle();
						velZHandle->constant(0);
					}

				}


			} else {

				if (f!=oldf) {

					fluidSolver->solveFluid();

				}

				if (COPYDENS(t)) {

					cu::cudaMemcpy( fluidSolver->host_dens, fluidSolver->dev_dens,
					fluidSolver->res.width*fluidSolver->res.height*fluidSolver->res.depth*sizeof(float), cu::cudaMemcpyDeviceToHost );

					{
						UT_VoxelArrayWriteHandleF	handle = volume->getVoxelWriteHandle();

						handle->size(fluidSolver->res.width, fluidSolver->res.height, fluidSolver->res.depth);

						for (int i = 0; i < fluidSolver->res.width; i++) {
							for (int j = 0; j < fluidSolver->res.height; j++) {
								for (int k = 0; k < fluidSolver->res.depth; k++) {
									handle->setValue(i, j, k, fluidSolver->host_dens[k*fluidSolver->res.width*fluidSolver->res.height + j*fluidSolver->res.width + i]);
								}
							}
						}
									

					}

					if (COPYVEL(t)) {

					cu::cudaMemcpy( fluidSolver->host_vel, fluidSolver->dev_vel,
						fluidSolver->res.width*fluidSolver->res.height*fluidSolver->res.depth*sizeof(cu::float4), cu::cudaMemcpyDeviceToHost );

					{
						UT_VoxelArrayWriteHandleF	velXHandle = velXVolume->getVoxelWriteHandle();
						velXHandle->size(fluidSolver->res.width, fluidSolver->res.height, fluidSolver->res.depth);
						UT_VoxelArrayWriteHandleF	velYHandle = velYVolume->getVoxelWriteHandle();
						velYHandle->size(fluidSolver->res.width, fluidSolver->res.height, fluidSolver->res.depth);
						UT_VoxelArrayWriteHandleF	velZHandle = velZVolume->getVoxelWriteHandle();
						velZHandle->size(fluidSolver->res.width, fluidSolver->res.height, fluidSolver->res.depth);

						
						for (int i = 0; i < fluidSolver->res.width; i++) {
							for (int j = 0; j < fluidSolver->res.height; j++) {
								for (int k = 0; k < fluidSolver->res.depth; k++) {
									velXHandle->setValue(i, j, k, fluidSolver->host_vel[4*(k*fluidSolver->res.width*fluidSolver->res.height + j*fluidSolver->res.width + i)]);
									velYHandle->setValue(i, j, k, fluidSolver->host_vel[4*(k*fluidSolver->res.width*fluidSolver->res.height + j*fluidSolver->res.width + i)+1]);
									velZHandle->setValue(i, j, k, fluidSolver->host_vel[4*(k*fluidSolver->res.width*fluidSolver->res.height + j*fluidSolver->res.width + i)+2]);
								}
							}
						}
									

					}


					}

				}
			}


		select(GU_SPrimitive);
		}

		// Tell the interrupt server that we've completed. Must do this
		// regardless of what opStart() returns.
		boss->opEnd();
    }

    gdp->notifyCache(GU_CACHE_ALL);

 
    return error();
}