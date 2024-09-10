void daBalboa_c::setupModels() {
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	nw4r::g3d::ResMdl mdl;
	nw4r::g3d::ResAnmChr anmChr;

	this->resFile.data = getResource("choropoo", "g3d/choropoo.brres");

	mdl = this->resFile.GetResMdl("choropoo");
	this->bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_Enemy(&this->bodyModel, 0);

	anmChr = this->resFile.GetResAnmChr("throw_1"); // 11
	this->animationChr.setup(mdl, anmChr, &this->allocator, 0);

	nw4r::g3d::ResFile togeRes;
	togeRes.data = getResource("lift_zen", "g3d/lift_zen.brres");
	mdl = togeRes.GetResMdl("lift_togeU");
	spikesModel.setup(mdl, &allocator, 0, 1, 0);

	// throw_1 // 11
	// throw_2 // 75
	// throw_3 // 33
	// throw_4_left_hand // 87
	// throw_4_right_hand // 87
	// throw_5 // 23

	allocator.unlink();
}