void lggBeamMaps::fireCurrentBeams(LLPointer<LLHUDEffectSpiral> mBeam, LLColor4U rgb)
{
	if (scale == 0.0f)
	{
		return;
	}

	static LLCachedControl<std::string> colorf(gSavedSettings, "FSBeamColorFile");
	bool colorsDisabled = std::string(colorf) == "===OFF===";
	
	for(int i = 0; i < (int)dots.size(); i++)
	{
		LLColor4U myColor = rgb;
		if (colorsDisabled) myColor = dots[i].c;

		F32 distanceAdjust = dist_vec(mBeam->getPositionGlobal(),gAgent.getPositionGlobal()) ;
		F32 pulse = (F32)(.75f+sinf(gFrameTimeSeconds*1.0f)*0.25f);
		LLVector3d offset = dots[i].p;
		offset.mdV[VY] *= -1;
		offset *= pulse * scale * distanceAdjust * 0.1;
		
		//llinfos << "dist is " << distanceAdjust << "scale is " << scale << llendl;
		LLVector3 beamLine = LLVector3( mBeam->getPositionGlobal() - gAgent.getPositionGlobal());
		LLVector3 beamLineFlat = beamLine;
		beamLineFlat.mV[VZ]= 0.0f;

		LLVector3 newDirFlat = LLVector3::x_axis;
		beamLine.normalize();
		beamLineFlat.normalize();
		LLQuaternion change;
		change.shortestArc(newDirFlat,beamLineFlat);
		offset.rotVec(change);
		newDirFlat.rotVec(change);
		change.shortestArc(newDirFlat,beamLine);
		offset.rotVec(change);

		LLPointer<LLHUDEffectSpiral> myBeam =  (LLHUDEffectSpiral *)LLHUDManager::getInstance()->createViewerEffect(LLHUDObject::LL_HUD_EFFECT_BEAM);
		myBeam->setPositionGlobal(mBeam->getPositionGlobal() + offset + (LLVector3d(beamLine) * sinf(gFrameTimeSeconds*2.0f) * 0.2f));
		
		myBeam->setColor(myColor);
		myBeam->setTargetObject(mBeam->getTargetObject());
		myBeam->setSourceObject(mBeam->getSourceObject());
		myBeam->setNeedsSendToSim(mBeam->getNeedsSendToSim());
		myBeam->setDuration(duration* 1.2f);
	}
}