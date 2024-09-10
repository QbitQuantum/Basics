OP_ERROR SOP_FluidSolver2D::cookMySop(OP_Context &context) {

	oldf = f;

	double t = context.getTime();
	int f =	context.getFrame();
	UT_Interrupt	*boss;
	GU_PrimVolume	*volume;

	OP_Node::flags().timeDep = 1;
	fluidSolver->fps = OPgetDirector()->getChannelManager()->getSamplesPerSec();


	int newResX = RESX(t);
	int newResY = RESY(t);

	if ( newResX != fluidSolver->res.x || newResY != fluidSolver->res.y) {
		fluidSolver->changeFluidRes(newResX,newResY);

	}

	UT_Vector3 fluidPos(POSX(t), POSY(t), POSZ(t));
	UT_Vector3 fluidRot(ROTX(t), ROTY(t), ROTZ(t));
	fluidRot.degToRad();

	fluidSolver->fluidSize.x = FLUIDSIZEX(t);
	fluidSolver->fluidSize.y = FLUIDSIZEY(t);

	fluidSolver->borderNegX = BORDERNEGX(t);
	fluidSolver->borderPosX = BORDERPOSX(t);
	fluidSolver->borderNegY = BORDERNEGY(t);
	fluidSolver->borderPosY = BORDERPOSY(t);

	fluidSolver->preview = PREVIEW(t);
	fluidSolver->previewType = PREVIEWTYPE(t);
	fluidSolver->bounds = BOUNDS(t);

	fluidSolver->substeps = SUBSTEPS(t);
	fluidSolver->jacIter = JACITER(t);

	fluidSolver->densDis = DENSDIS(t);
	fluidSolver->densBuoyStrength = DENSBUOYSTRENGTH(t);
	float ddirX = DENSBUOYDIRX(t);
	float ddirY = DENSBUOYDIRY(t);
	fluidSolver->densBuoyDir = cu::make_float2(ddirX,ddirY);

	fluidSolver->velDamp = VELDAMP(t);
	fluidSolver->vortConf = VORTCONF(t);

	fluidSolver->noiseStr = NOISESTR(t);
	fluidSolver->noiseFreq = NOISEFREQ(t);
	fluidSolver->noiseOct = NOISEOCT(t);
	fluidSolver->noiseLacun = NOISELACUN(t);
	fluidSolver->noiseSpeed = NOISESPEED(t);
	fluidSolver->noiseAmp = NOISEAMP(t);

    if (error() < UT_ERROR_ABORT) {
			boss = UTgetInterrupt();

		gdp->clearAndDestroy();		

		// Start the interrupt server
		if (boss->opStart("Building Volume")){

			static float		 zero = 0.0;

#ifdef HOUDINI_11
			GB_AttributeRef fluidAtt = gdp->addAttrib("cudaFluidPreview", sizeof(int), GB_ATTRIB_INT, &zero);
			gdp->attribs().getElement().setValue<int>(fluidAtt, fluidSolver->preview);

			GB_AttributeRef solverIdAtt = gdp->addAttrib("solverId", sizeof(int), GB_ATTRIB_INT, &zero);
			gdp->attribs().getElement().setValue<int>(solverIdAtt, fluidSolver->id);
#else
			GA_WOAttributeRef fluidAtt = gdp->addIntTuple(GA_ATTRIB_DETAIL, "cudaFluidPreview", 1);
			gdp->element().setValue<int>(fluidAtt, fluidSolver->preview);

			GA_WOAttributeRef solverIdAtt = gdp->addIntTuple(GA_ATTRIB_DETAIL, "solverId", 1);
			gdp->element().setValue<int>(solverIdAtt, fluidSolver->id);
#endif


			UT_Matrix3              xform;
			const UT_XformOrder volXFormOrder;
			
			volume = (GU_PrimVolume *)GU_PrimVolume::build(gdp);

#ifdef HOUDINI_11
			volume->getVertex().getPt()->getPos() = fluidPos;
#else
			volume->getVertexElement(0).getPt()->setPos(fluidPos);
#endif

			xform.identity();
			xform.scale(fluidSolver->fluidSize.x*0.5, fluidSolver->fluidSize.y*0.5, 0.25);
			xform.rotate(fluidRot.x(), fluidRot.y(), fluidRot.z(), volXFormOrder);

			volume->setTransform(xform);
			

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
					fluidSolver->emitters = new FluidEmitter[numEmitters];
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
					fluidSolver->colliders = new Collider[numColliders];
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
					} else {
						fluidSolver->colliders[i].oldPosX = colPos3.x();
						fluidSolver->colliders[i].oldPosY = colPos3.y();
					}

					fluidSolver->colliders[i].posX = colPos3.x();
					fluidSolver->colliders[i].posY = colPos3.y();

					colRadAh.setElement(collidersList[i]);

					fluidSolver->colliders[i].radius = colRadAh.getF(0);
				}

			} else {
				fluidSolver->nColliders = 0;
			}

			unlockInputs();

			if (f <= STARTFRAME(t)) {

				fluidSolver->resetFluid();

				if (fluidSolver->preview != 1) {
					{
						UT_VoxelArrayWriteHandleF	handle = volume->getVoxelWriteHandle();
						handle->constant(0);
					}
				}


			} else {

				if (f!=oldf) {

					fluidSolver->solveFluid();

				}

				if (fluidSolver->preview != 1) {
					
						cu::cudaMemcpy( fluidSolver->host_dens, fluidSolver->dev_dens,
						fluidSolver->res.x*fluidSolver->res.y*sizeof(float), cu::cudaMemcpyDeviceToHost );
				
					{
						UT_VoxelArrayWriteHandleF	handle = volume->getVoxelWriteHandle();

						handle->size(fluidSolver->res.x, fluidSolver->res.y, 1);

						for (int i = 0; i < fluidSolver->res.x; i++) {
							for (int j = 0; j < fluidSolver->res.y; j++) {
								handle->setValue(i, j, 0, fluidSolver->host_dens[(j*fluidSolver->res.x + i)]);
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