int daKoopaThrow::onCreate() {

	this->direction = this->settings & 0xF;
	this->Type = (this->settings >> 4) & 0xF;
	this->front = (this->settings >> 8) & 0xF;

	currentInfo = &types[Type];

	allocator.link(-1, GameHeaps[0], 0, 0x20);

	nw4r::g3d::ResFile rf(getResource(currentInfo->arcName, currentInfo->brresName));
	nw4r::g3d::ResMdl resMdl = rf.GetResMdl(currentInfo->modelName);

	bodyModel.setup(resMdl, &allocator, (Type == 4 ? 0x224 : 0), 1, 0);
	SetupTextures_Enemy(&bodyModel, 0);

	if (Type == 4) {
		// Thwomp
		playsAnim = true;

		nw4r::g3d::ResAnmChr anmChr = rf.GetResAnmChr("boss_throw");
		chrAnim.setup(resMdl, anmChr, &allocator, 0);
		chrAnim.bind(&bodyModel, anmChr, 1);
		bodyModel.bindAnim(&chrAnim, 0.0);
		chrAnim.setUpdateRate(1.0);
	}

	allocator.unlink();


	ActivePhysics::Info KoopaJunk;

	KoopaJunk.xDistToCenter = 0.0f;
	KoopaJunk.yDistToCenter = (Type == 4) ? currentInfo->size : 0.0;
	KoopaJunk.xDistToEdge = currentInfo->size;
	KoopaJunk.yDistToEdge = currentInfo->size;

	this->scale.x = currentInfo->scale;
	this->scale.y = currentInfo->scale;
	this->scale.z = currentInfo->scale;

	KoopaJunk.category1 = 0x3;
	KoopaJunk.category2 = 0x0;
	KoopaJunk.bitfield1 = 0x47;
	KoopaJunk.bitfield2 = 0xFFFFFFFF;
	KoopaJunk.unkShort1C = 0;
	KoopaJunk.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &KoopaJunk);
	this->aPhysics.addToList();


	spriteSomeRectX = currentInfo->size;
	spriteSomeRectY = currentInfo->size;
	_320 = 0.0f;
	_324 = currentInfo->size;

	// These structs tell stupid collider what to collide with - these are from koopa troopa
	static const lineSensor_s below(12<<12, 4<<12, 0<<12);
	static const pointSensor_s above(0<<12, 12<<12);
	static const lineSensor_s adjacent(6<<12, 9<<12, 6<<12);

	collMgr.init(this, &below, &above, &adjacent);
	collMgr.calculateBelowCollisionWithSmokeEffect();

	cmgr_returnValue = collMgr.isOnTopOfTile();


	if (this->direction == 0) 	   { // Ground Facing Left
		this->pos.x -= 0.0; // -32 to +32
		this->pos.y += 36.0;
		// this->rot.z = 0x2000;
	}
	else if (this->direction == 1) { // Ground Facing Right
		this->pos.x += 0.0; // +32 to -32
		this->pos.y += 36.0;
		// this->rot.z = 0xE000;
	}
	if (this->front == 1) { this->pos.z = -1804.0; }
	else 				  { this->pos.z =  3300.0; }


	if (currentInfo->launchSound != 0) {
		PlaySound(this, currentInfo->launchSound);
	}

	if (Type == 3) {
		PlaySoundWithFunctionB4(SoundRelatedClass, &hammerSound, SE_EMY_MEGA_BROS_HAMMER, 1);
	}

	doStateChange(&StateID_Straight);

	this->onExecute();
	return true;
}