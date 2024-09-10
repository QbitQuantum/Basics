int daEnFlipBlock_c::onCreate() {
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	resFile.data = getResource("block_rotate", "g3d/block_rotate.brres");
	model.setup(resFile.GetResMdl("block_rotate"), &allocator, 0, 1, 0);
	SetupTextures_MapObj(&model, 0);

	allocator.unlink();



	blockInit(pos.y);

	physicsInfo.x1 = -8;
	physicsInfo.y1 = 8;
	physicsInfo.x2 = 8;
	physicsInfo.y2 = -8;

	physicsInfo.otherCallback1 = &daEnBlockMain_c::OPhysicsCallback1;
	physicsInfo.otherCallback2 = &daEnBlockMain_c::OPhysicsCallback2;
	physicsInfo.otherCallback3 = &daEnBlockMain_c::OPhysicsCallback3;

	physics.setup(this, &physicsInfo, 3, currentLayerID);
	physics.flagsMaybe = 0x260;
	physics.callback1 = &daEnBlockMain_c::PhysicsCallback1;
	physics.callback2 = &daEnBlockMain_c::PhysicsCallback2;
	physics.callback3 = &daEnBlockMain_c::PhysicsCallback3;
	physics.addToList();

	doStateChange(&daEnFlipBlock_c::StateID_Wait);

	return true;
}