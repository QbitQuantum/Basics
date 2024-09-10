void grAddSmoke(tCarElt *car, double t)
{
	int i = 0;
	tgrSmoke * tmp;
	sgVec3 vtx;
	ssgVertexArray *shd_vtx ;
	tgrCarInstrument *curInst;
	tdble val;
	int index;

	if (!grSmokeMaxNumber) {
		return;
	}

	for (i = 0; i < 4; i++) {
		if (car->pub.speed > 0.03f) {	// 0.03 -> sqrt(0.001)
			if (smokeManager->number < grSmokeMaxNumber) {
				if ((t - timeSmoke[car->index*4+i]) < grSmokeDeltaT) {
					continue;
				} else {
					timeSmoke[car->index*4+i] = t;
				}

				sgVec3 cur_clr;
				tdble init_speed;
				tdble threshold = 0.1f;
				tdble smoke_life_coefficient = 30.0f;
				tdble smoke_speed_coefficient = 0.0f;

				cur_clr[0] = 0.8f;
				cur_clr[1] = 0.8f;
				cur_clr[2] = 0.8f;
				init_speed = 0.01f;

				if (car->priv.wheel[i].seg) { // sanity check
					const char* surface = car->priv.wheel[i].seg->surface->material;
					if (strstr(surface, "sand")) {
						cur_clr[0] = 0.8f;
						cur_clr[1] = 0.7f + urandom()*0.1f;
						cur_clr[2] = 0.4f + urandom()*0.2f;
						init_speed = 0.5f;
						threshold = 0.05f;
						smoke_life_coefficient = 12.5f;
						smoke_speed_coefficient = 0.25f;
					} else if (strstr(surface, "dirt")) {
						cur_clr[0] = 0.7f + urandom()*0.1f;
						cur_clr[1] = 0.6f + urandom()*0.1f;
						cur_clr[2] = 0.5f + urandom()*0.1f;
						init_speed = 0.45f;
						threshold=0.0f;
						smoke_life_coefficient = 10.0f;
						smoke_speed_coefficient = 0.5f;
					} else if (strstr(surface,"mud")) {
						cur_clr[0] = 0.65f;
						cur_clr[1] = 0.4f + urandom()*0.2f;
						cur_clr[2] = 0.3f + urandom()*0.2f;
						init_speed = 0.4f;
						threshold = 0.2f;
						smoke_speed_coefficient = 0.05f;
					} else if (strstr(surface,"gravel")) {
						cur_clr[0] = 0.6f;
						cur_clr[1] = 0.6f;
						cur_clr[2] = 0.6f;
						init_speed = 0.35f;
						smoke_life_coefficient = 20.0f;
						smoke_speed_coefficient = 0.1f;
					} else if (strstr(surface,"grass")) {
						cur_clr[0] = 0.4f + urandom()*0.2f;
						cur_clr[1] = 0.5f + urandom()*0.1f;
						cur_clr[2] = 0.3f + urandom()*0.1f;
						init_speed = 0.3f;
						smoke_life_coefficient = 25.0f;
					} else {
						cur_clr[0] = 0.8f;
						cur_clr[1] = 0.8f;
						cur_clr[2] = 0.8f;
						init_speed = 0.01f;
					}
				}

				smoke_life_coefficient = smoke_life_coefficient * (1.0f - urandom()*urandom());
				tdble spd_fx=tanh(0.001f*car->_reaction[i])*smoke_speed_coefficient*car->pub.speed;
				if (car->_skid[i] + 0.025f*urandom()*spd_fx>urandom() + threshold) {// instead of 0.3, to randomize

					float init_speed_z = 0.1f;
					float stretch_factor = 0.5f;
					tdble sinCarYaw = sin(car->_yaw);
					tdble cosCarYaw = cos(car->_yaw);

					shd_vtx = new ssgVertexArray(1);
					//shd_clr = new ssgColourArray(1);

					tmp = (tgrSmoke *) malloc(sizeof(tgrSmoke));
					vtx[0] = car->priv.wheel[i].relPos.x;
					vtx[1] = car->priv.wheel[i].relPos.y;
					vtx[2] = car->priv.wheel[i].relPos.z-car->_wheelRadius(i)*1.0f+ 0.5f * SMOKE_INIT_SIZE;
					tdble stretchX = 0.1f * (spd_fx + stretch_factor * fabs(car->_speed_X));
					tdble stretchY = 0.1f * (spd_fx + stretch_factor * fabs(car->_speed_Y));
					vtx[0] -= 0.05f*car->_speed_x;

					shd_vtx->add(vtx);
					tmp->smoke = new ssgVtxTableSmoke(shd_vtx,SMOKE_INIT_SIZE,SMOKE_TYPE_TIRE);
					init_speed = urandom()*init_speed;

					tmp->smoke->vvx = -sinCarYaw * car->_wheelSlipSide(i);
					tmp->smoke->vvy = cosCarYaw * car->_wheelSlipSide(i);
					tmp->smoke->vvx += cosCarYaw * car->_wheelSlipAccel(i);
					tmp->smoke->vvy += sinCarYaw * car->_wheelSlipAccel(i);

					tmp->smoke->vvz = init_speed_z;

					tmp->smoke->vvx *= init_speed;
					tmp->smoke->vvy *= init_speed;
					tmp->smoke->setState(mst);
					tmp->smoke->setCullFace(0);

					//printf("%f\n", car->_reaction[i]);
					tmp->smoke->max_life = grSmokeLife *
						(car->_skid[i]*car->pub.speed+urandom()*spd_fx)/ smoke_life_coefficient;
					for (int c = 0; c < 3; c++) {
						tmp->smoke->cur_col[c] = cur_clr[c];
					}

					tmp->smoke->cur_life = 0;
					tmp->smoke->sizex = VX_INIT + stretchX;
					tmp->smoke->sizey = VY_INIT + stretchY;
					tmp->smoke->sizez = VZ_INIT + 0.1f * spd_fx;

					tmp->smoke->init_alpha = 1.0/(1.0+0.1*spd_fx);
					tmp->smoke->vexp = V_EXPANSION+(car->_skid[i]+.1*spd_fx)*(((float)rand()/(float)RAND_MAX));
					tmp->smoke->smokeType = SMOKE_TYPE_TIRE;
					tmp->smoke->smokeTypeStep = 0;
					tmp->next = NULL;
					tmp->smoke->lastTime = t;
					tmp->smoke->transform(grCarInfo[car->index].carPos);
					SmokeAnchor->addKid(tmp->smoke);
					smokeManager->number++;
					if (smokeManager->smokeList==NULL) {
						smokeManager->smokeList = tmp;
					} else {
						tmp->next = smokeManager->smokeList;
						smokeManager->smokeList = tmp;
					}
				}
			}
		}
    }

    if (car->_exhaustNb && (car->pub.speed > 3.0f)) {
		if (smokeManager->number < grSmokeMaxNumber) {
			index = car->index;	/* current car's index */
			if ((t - timeFire[index]) > grFireDeltaT) {
				timeFire[index] = t;
				curInst = &(grCarInfo[index].instrument[0]);
				val = ((curInst->rawPrev - curInst->minValue) / curInst->maxValue) - ((*(curInst->monitored) - curInst->minValue) / curInst->maxValue);
				curInst->rawPrev = *(curInst->monitored);
				if (val > 0.1) {
					grCarInfo[index].fireCount = (int)(10.0 * val * car->_exhaustPower);
				}

				if (grCarInfo[index].fireCount) {
					grCarInfo[index].fireCount--;
				//if (car->priv.smoke>urandom()) {
			
					//car->priv.smoke = val * car->_exhaustPower;
					for (i = 0; i < car->_exhaustNb; i++) {
						shd_vtx = new ssgVertexArray(1);
						tmp = (tgrSmoke *) malloc(sizeof(tgrSmoke));
						vtx[0] = car->_exhaustPos[i].x;
						vtx[1] = car->_exhaustPos[i].y;
						vtx[2] = car->_exhaustPos[i].z;
		    
						shd_vtx->add(vtx);
						tmp->smoke = new ssgVtxTableSmoke(shd_vtx,SMOKE_INIT_SIZE*4,SMOKE_TYPE_ENGINE);

						tmp->smoke->setState(mstf0);
						tmp->smoke->setCullFace(0);
						tmp->smoke->max_life = grSmokeLife/8;
						tmp->smoke->step0_max_life =  (grSmokeLife)/50.0;
						tmp->smoke->step1_max_life =  (grSmokeLife)/50.0+ tmp->smoke->max_life/2.0;
						tmp->smoke->cur_life = 0;
						//tmp->smoke->init_alpha = 0.9;
						tmp->smoke->sizex = VX_INIT*4;
						tmp->smoke->sizey = VY_INIT*4;
						tmp->smoke->sizez = VZ_INIT*4;
						tmp->smoke->vexp = V_EXPANSION+5.0*rand()/(RAND_MAX+1.0) * car->_exhaustPower / 2.0;
						//tmp->smoke->vexp = V_EXPANSION+5.0*(((float)rand()/(float)RAND_MAX)) * car->_exhaustPower / 2.0;
						tmp->smoke->smokeType = SMOKE_TYPE_ENGINE;
						tmp->smoke->smokeTypeStep = 0;
						tmp->next = NULL;
						tmp->smoke->lastTime = t;
						tmp->smoke->transform(grCarInfo[index].carPos);
						SmokeAnchor->addKid(tmp->smoke);
						smokeManager->number++;
						if (smokeManager->smokeList==NULL) {
							smokeManager->smokeList = tmp;
						} else {
							tmp->next = smokeManager->smokeList;
							smokeManager->smokeList = tmp;
						}
					}
				}
			}
		}
    }
}