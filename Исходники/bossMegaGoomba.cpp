void daMegaGoomba_c::setupBodyModel() {
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("kuriboBoss", "g3d/kuriboBoss.brres");
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("kuriboBig");
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_Enemy(&bodyModel, 0);

	bool ret;
	nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr("walk");
	ret = this->animationChr.setup(mdl, anmChr, &this->allocator, 0);
	this->bindAnimChr_and_setUpdateRate("walk", 1, 0.0, 0.2);

	allocator.unlink();
}