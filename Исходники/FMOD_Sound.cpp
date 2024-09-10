void FMOD_Sound::addEffect(int module_id, int type, float value)
{
	float normalized_value = value / 100.0f;

	switch(type)
	{
		case Reverb:
			FMOD::DSP * reverb;
			system->createDSPByType(FMOD_DSP_TYPE_REVERB, &reverb);
			channelMap[module_id]->addDSP(reverb, 0);
			reverb->setParameter(FMOD_DSP_REVERB_ROOMSIZE, normalized_value);
			reverbMap[module_id] = reverb;
			break;
		case Pitch:
			FMOD::DSP * pitch;
			system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &pitch);
			channelMap[module_id]->addDSP(pitch, 0);
			pitch->setParameter(0, normalized_value);
			pitchMap[module_id] = pitch;
			break;
		case Distortion:
			FMOD::DSP * distortion;
			system->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &distortion);
			channelMap[module_id]->addDSP(distortion, 0);
			distortion->setParameter(0, normalized_value);
			distortionMap[module_id] = distortion;
			break;
		case Echo:
			FMOD::DSP * echo;
			system->createDSPByType(FMOD_DSP_TYPE_ECHO, &echo);
			channelMap[module_id]->addDSP(echo, 0);
			echo->setParameter(0, normalized_value);
			echoMap[module_id] = echo;
			break;
		case Flange:
			FMOD::DSP * flange;
			system->createDSPByType(FMOD_DSP_TYPE_FLANGE, &flange);
			channelMap[module_id]->addDSP(flange, 0);
			flange->setParameter(0, normalized_value);
			flangeMap[module_id] = flange;
			break;
		default:
			break;
	}
}