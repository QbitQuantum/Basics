	SPtr<AnimationClip> AnimationClip::_createPtr(const SPtr<AnimationCurves>& curves, bool isAdditive, UINT32 sampleRate, 
		const SPtr<RootMotion>& rootMotion)
	{
		AnimationClip* rawPtr = new (bs_alloc<AnimationClip>()) AnimationClip(curves, isAdditive, sampleRate, rootMotion);

		SPtr<AnimationClip> newClip = bs_core_ptr<AnimationClip>(rawPtr);
		newClip->_setThisPtr(newClip);
		newClip->initialize();

		return newClip;
	}