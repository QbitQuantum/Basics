void daRamboo_c::setupModels() {
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("teresa", "g3d/teresa.brres");
	bool ret;

	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("fog");
	this->fogModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_Enemy(&this->fogModel, 0);

	nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr("fog");
	ret = this->anmFog.setup(mdl, anmChr, &this->allocator, 0);


	nw4r::g3d::ResMdl mdlB = this->resFile.GetResMdl("teresaA");
	this->bodyModel.setup(mdlB, &allocator, 0x224, 1, 0);
	SetupTextures_Enemy(&this->bodyModel, 0);

	nw4r::g3d::ResAnmChr anmChrC = this->resFile.GetResAnmChr("shay_teresaA");
	ret = this->anmA.setup(mdlB, anmChrC, &this->allocator, 0);


	nw4r::g3d::ResMdl mdlC = this->resFile.GetResMdl("teresaB");
	this->hideModel.setup(mdlC, &allocator, 0x224, 1, 0);
	SetupTextures_Enemy(&this->hideModel, 0);

	nw4r::g3d::ResAnmChr anmChrE = this->resFile.GetResAnmChr("shay_teresaB");
	ret = this->anmB.setup(mdlC, anmChrE, &this->allocator, 0);

	nw4r::g3d::ResAnmTexSrt anmSrt = this->resFile.GetResAnmTexSrt("fog");
	this->resTexSrt = anmSrt;
	//setup(ResMdl mdl, ResAnmTexSrt anmSrt, mAllocator* allocator, void* NULL, int count);
	ret = this->fogSrt.setup(mdl, anmSrt, &this->allocator, 0, 1);
	//setEntryByte34(char toSet, int which);
	this->fogSrt.setEntryByte34(0, 0);

	allocator.unlink();
}