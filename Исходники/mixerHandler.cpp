void mh_loadPatch(bool isProject, const char *projPath)
{
	G_Mixer.init();
	G_Mixer.ready = false;   // put it in wait mode

	int numChans = G_Patch.getNumChans();
	for (int i=0; i<numChans; i++) {

		Channel *ch = glue_addChannel(G_Patch.getColumn(i), G_Patch.getType(i));

		char smpPath[PATH_MAX];

		/* projects < 0.6.3 version are not portable. Just use the regular
		 * samplePath */
		/* TODO version >= 0.10.0 - old stuff, remove backward compatibility */

		if (isProject && G_Patch.version >= 0.63f)
			sprintf(smpPath, "%s%s%s", gDirname(projPath).c_str(), gGetSlash().c_str(), G_Patch.getSamplePath(i).c_str());
		else
			sprintf(smpPath, "%s", G_Patch.getSamplePath(i).c_str());

		ch->loadByPatch(smpPath, i);
	}

	G_Mixer.outVol     = G_Patch.getOutVol();
	G_Mixer.inVol      = G_Patch.getInVol();
	G_Mixer.bpm        = G_Patch.getBpm();
	G_Mixer.bars       = G_Patch.getBars();
	G_Mixer.beats      = G_Patch.getBeats();
	G_Mixer.quantize   = G_Patch.getQuantize();
	G_Mixer.metronome  = G_Patch.getMetronome();
	G_Patch.lastTakeId = G_Patch.getLastTakeId();
	G_Patch.samplerate = G_Patch.getSamplerate();

	/* rewind and update frames in Mixer (it's vital) */

	G_Mixer.rewind();
	G_Mixer.updateFrameBars();
	G_Mixer.ready = true;
}