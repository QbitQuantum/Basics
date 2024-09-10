//----------------------------------------------------------------------------
void BeamEmitterController::EmitABeam (float ctrlTime)
{
	BeamEmitter *emitter = (BeamEmitter*)mObject;
	ModulesUpdateEffectable(ctrlTime);

	Camera *cam = Renderer::GetDefaultRenderer()->GetCamera();
	const AVector &camD = cam->GetDVector();

	Effectable::FaceType faceType = emitter->GetFaceType();
	BeamEmitter::WaveType waveTypeUp = emitter->GetWaveTypeUp();
	BeamEmitter::WaveType waveTypeExtend = emitter->GetWaveTypeExtend();
	int numLowFre = emitter->GetNumLowFrequency();
	int numHighFre = emitter->GetNumHighFrequency();
	const Float2 &lowFreRangeUp = emitter->GetLowFrequencyRangeUp();
	const Float2 &lowFreRangeExtend = emitter->GetLowFrequencyRangeExtend();
	const Float2 &hightFreRangeUp = emitter->GetHighFrequencyRangeUp();
	const Float2 &hightFreRangeExtend = emitter->GetHighFrequencyRangeExtend();
	APoint emitStartPos = emitter->GetEmitStartPos();
	const APoint &emitEndPos = emitter->GetEmitEndPos();

	if (emitter->IsStartPosUseLocal() && !emitter->IsLocal())
	{
		emitStartPos = emitter->WorldTransform * emitStartPos;
	}

	BeamObject obj;
	obj.StartPos = emitStartPos;
	obj.EndPos = emitEndPos;

	AVector dirVec = emitEndPos - emitStartPos;
	if (dirVec == AVector::ZERO)
	{
		dirVec.X() = 0.01f;
	}
	AVector dir = dirVec;
	dir.Normalize();

	AVector toMeDir;
	if (Effectable::FT_X == faceType)
	{
		toMeDir = AVector::UNIT_X;
	}
	else if (Effectable::FT_NX == faceType)
	{
		toMeDir = -AVector::UNIT_X;
	}
	else if (Effectable::FT_Y == faceType)
	{
		toMeDir = AVector::UNIT_Y;
	}
	else if (Effectable::FT_NY == faceType)
	{
		toMeDir = -AVector::UNIT_Y;
	}
	else if (Effectable::FT_Z == faceType)
	{
		toMeDir = AVector::UNIT_Z;
	}
	else if (Effectable::FT_NZ == faceType)
	{
		toMeDir = -AVector::UNIT_Z;
	}
	else if (Effectable::FT_CAMERA == faceType || 
		Effectable::FT_SPEEDDIR==faceType || 
		Effectable::FT_FREE==faceType)
	{
		toMeDir = -camD;
	}

	AVector upDir = toMeDir.Cross(dir);
	upDir.Normalize();
	AVector toMeExtendDir = dir.Cross(upDir);
	toMeExtendDir.Normalize();

	int numLowFreNumPoints = numLowFre+1;

	std::vector<float> upLFs, toMeLFs;

	if (BeamEmitter::WT_RANDOM==waveTypeUp || BeamEmitter::WT_LINE==waveTypeUp)
	{
		GernerateLFPoints(upLFs, numLowFreNumPoints, waveTypeUp, lowFreRangeUp[0], lowFreRangeUp[1]);
	}
	else
	{
	}

	if (BeamEmitter::WT_RANDOM==waveTypeExtend || BeamEmitter::WT_LINE==waveTypeExtend)
	{
		GernerateLFPoints(toMeLFs, numLowFreNumPoints, waveTypeExtend, lowFreRangeExtend[0], lowFreRangeExtend[1]);
	}
	else
	{
	}

	APoint lastPoint;
	for (int i=0; i<numLowFreNumPoints; i++)
	{
		APoint lPos = emitStartPos + dirVec * (i/(float)(numLowFreNumPoints-1));
		APoint lPoint = lPos + upDir*upLFs[i] + toMeExtendDir * toMeLFs[i];

		if (0 != i)
		{
			for (int k=1; k<numHighFre; k++)
			{
				AVector hVec = lPoint - lastPoint;
				APoint hPoint = lastPoint + hVec * (k/(float)numHighFre);
				hPoint += upDir * Mathf::IntervalRandom(hightFreRangeUp[0], hightFreRangeUp[1]);
				hPoint += toMeExtendDir * Mathf::IntervalRandom(hightFreRangeExtend[0], hightFreRangeExtend[1]);

				obj.Points.push_back(hPoint);
			}
		}

		obj.Points.push_back(lPoint);

		lastPoint = lPoint;
	}

	OnNewAEffectObject(&obj);

	ModulesUpdateEffectObject(&obj);

	mBeamObjects.push_back(obj);
}