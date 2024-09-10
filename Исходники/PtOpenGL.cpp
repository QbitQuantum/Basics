void GLPresenter::testAAinternal()
{
	const char* ts = timeString();
	GLRenderTexture target(getW(), getH(), GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);

	AAManager::aaMode prevMode = aaManager->getAAMode();

	aaManager->setAAMode(AAManager::NONE);
	aaManager->applyAA(buffer, &target);
	target.saveToImage(format("%s__noaa.png", ts));
	aaManager->setAAMode(AAManager::FXAA);
	aaManager->applyAA(buffer, &target);
	target.saveToImage(format("%s__fxaa.png", ts));
	aaManager->setAAMode(AAManager::PXAA);
	aaManager->applyAA(buffer, &target);
	target.saveToImage(format("%s__pxaa.png", ts));
	aaManager->setAAMode(AAManager::TPXAA);
	aaManager->applyAA(buffer, &target);
	target.saveToImage(format("%s__tpxaa.png", ts));
	aaManager->setAAMode(AAManager::SMAA);
	aaManager->applyAA(buffer, &target);
	target.saveToImage(format("%s__smaa.png", ts));


	aaManager->setAAMode(prevMode);
}