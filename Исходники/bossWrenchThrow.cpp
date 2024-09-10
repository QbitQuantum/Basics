int daWrench::onCreate() {

	allocator.link(-1, GameHeaps[0], 0, 0x20);

	nw4r::g3d::ResFile rf(getResource("choropoo", "g3d/choropoo.brres"));
	bodyModel.setup(rf.GetResMdl("spanner"), &allocator, 0x224, 1, 0);
	SetupTextures_Enemy(&bodyModel, 0);

	allocator.unlink();


	this->direction = this->settings & 0xF;
	this->Kaboom = (this->settings >> 4) & 0xF;
	this->front = (this->settings >> 8) & 0xF;

	ActivePhysics::Info HitMeBaby;

	if (this->Kaboom == 0) {
		HitMeBaby.xDistToCenter = 0.0;
		HitMeBaby.yDistToCenter = 0.0;
		HitMeBaby.xDistToEdge = 5.0;
		HitMeBaby.yDistToEdge = 5.0;

		this->scale.x = 1.25;
		this->scale.y = 1.25;
		this->scale.z = 1.25;
	}

	else {
		HitMeBaby.xDistToCenter = 0.0;
		HitMeBaby.yDistToCenter = 0.0;
		HitMeBaby.xDistToEdge = 8.0;
		HitMeBaby.yDistToEdge = 8.0;

		this->scale.x = 2.0;
		this->scale.y = 2.0;
		this->scale.z = 2.0;
	}

	HitMeBaby.category1 = 0x3;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x47;
	HitMeBaby.bitfield2 = 0xFFFFFFFF;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();


	spriteSomeRectX = 5.0f;
	spriteSomeRectY = 5.0f;
	_320 = 0.0f;
	_324 = 5.0f;

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
		this->rot.z = 0x2000;
	}
	else if (this->direction == 1) { // Ground Facing Right
		this->pos.x += 0.0; // +32 to -32
		this->pos.y += 36.0;
		this->rot.z = 0xE000;
	}
	if (this->front == 1) { this->pos.z = -1804.0; }
	else 				  { this->pos.z =  3300.0; }


	if (this->Kaboom) {
		doStateChange(&StateID_Kaboom); }
	else {
		doStateChange(&StateID_Straight); }

	this->onExecute();
	return true;
}