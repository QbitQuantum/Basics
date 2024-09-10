void AudioChannel::FindSourceAndPlay(size_t id, const float3& pos, const float3& velocity, float volume, bool relative)
{
	boost::recursive_mutex::scoped_lock lck(soundMutex);

	if (!enabled)
		return;

	if (volume <= 0.0f)
		return;

	SoundItem* sndItem = sound->GetSoundItem(id);
	if (!sndItem) {
		sound->numEmptyPlayRequests++;
		return;
	}

	if (pos.distance(sound->GetListenerPos()) > sndItem->MaxDistance()) {
		if (!relative) {
			return;
		} else {
			LOG("CSound::PlaySample: maxdist ignored for relative playback: %s",
					sndItem->Name().c_str());
		}
	}

	if (emmitsThisFrame >= emmitsPerFrame)
		return;
	emmitsThisFrame++;

	if (cur_sources.size() >= maxConcurrentSources) {
		CSoundSource* src = NULL;
		int prio = INT_MAX;
		for (std::map<CSoundSource*, bool>::iterator it = cur_sources.begin(); it != cur_sources.end(); ++it) {
			if (it->first->GetCurrentPriority() < prio) {
				src  = it->first;
				prio = it->first->GetCurrentPriority();
			}
		}

		if (src && prio <= sndItem->GetPriority()) {
			src->Stop();
		} else {
			LOG_L(L_DEBUG, "CSound::PlaySample: Max concurrent sounds in channel reached! Dropping playback!");
			return;
		}
	}

	CSoundSource* sndSource = sound->GetNextBestSource();
	if (!sndSource) {
		LOG_L(L_DEBUG, "CSound::PlaySample: Max sounds reached! Dropping playback!");
		return;
	}

	if (sndSource->GetCurrentPriority() < sndItem->GetPriority()) {
		if (sndSource->IsPlaying())
			sound->numAbortedPlays++;

		sndSource->Play(this, sndItem, pos, velocity, volume, relative);
		CheckError("CSound::FindSourceAndPlay");

		cur_sources[sndSource] = true;
	}
}