void GHEffectViews_createEffects(LinkedList* effectParams) {

	createDistortion(effectParams);
	createTremolo(effectParams);
	createCompressor(effectParams);
	createDelay(effectParams);
	createOctaver(effectParams);
	createBitCrusher(effectParams);
	createMaster(effectParams);
}