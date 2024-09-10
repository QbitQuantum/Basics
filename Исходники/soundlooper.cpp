void SoundLooper::bar() {
	if(!(bars % 4) && bars > play_to){
		bars = 0;
	}
	if(bars == start_at){
		int status_was = status;
		// Play sound
		if (status == LOOPER_QUEUED){
			status = LOOPER_PLAYING;
		}
	
		if (status == LOOPER_STOPPING){
			status = LOOPER_IDLE;
			gui->intEvent(EVENT_CHANGE_TRG_COLOR, COLOR_TRG_IDLE);
		}
		if (status == LOOPER_PLAYING){
			FMOD::Channel *ch;
			ERRCHECK(sound->system->playSound(FMOD_CHANNEL_FREE, sample, false, &ch));
			ERRCHECK(ch->setChannelGroup(cg));
		}
		if(status_was != status) {
			gui->intEvent(EVENT_CHANGE_TRG_COLOR, status==LOOPER_PLAYING?COLOR_TRG_PLAYING:COLOR_TRG_IDLE);
		}
	}

	if(bars == play_to) {
		bars = 0;
	}
	else
		bars++;
}