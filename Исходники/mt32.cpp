int MidiDriver_MT32::open() {
	if (_isOpen)
		return MERR_ALREADY_OPEN;

	_reportHandler = new MT32Emu::ReportHandlerScummVM();
	_synth = new MT32Emu::Synth(_reportHandler);

	Graphics::PixelFormat screenFormat = g_system->getScreenFormat();

	if (screenFormat.bytesPerPixel == 1) {
		const byte dummy_palette[] = {
			0, 0, 0,		// background
			0, 171, 0,	// border, font
			171, 0, 0	// fill
		};

		g_system->getPaletteManager()->setPalette(dummy_palette, 0, 3);
	}

	_initializing = true;
	debug(4, _s("Initializing MT-32 Emulator"));
	_controlFile = new Common::File();
	if (!_controlFile->open("CM32L_CONTROL.ROM") && !_controlFile->open("MT32_CONTROL.ROM"))
		error("Error opening MT32_CONTROL.ROM / CM32L_CONTROL.ROM");
	_pcmFile = new Common::File();
	if (!_pcmFile->open("CM32L_PCM.ROM") && !_pcmFile->open("MT32_PCM.ROM"))
		error("Error opening MT32_PCM.ROM / CM32L_PCM.ROM");
	_controlROM = MT32Emu::ROMImage::makeROMImage(_controlFile);
	_pcmROM = MT32Emu::ROMImage::makeROMImage(_pcmFile);
	if (!_synth->open(*_controlROM, *_pcmROM))
		return MERR_DEVICE_NOT_AVAILABLE;

	double gain = (double)ConfMan.getInt("midi_gain") / 100.0;
	_synth->setOutputGain(1.0f * gain);
	_synth->setReverbOutputGain(0.68f * gain);
	// We let the synthesizer play MIDI messages immediately. Our MIDI
	// handling is synchronous to sample generation. This makes delaying MIDI
	// events result in odd sound output in some cases. For example, the
	// shattering window in the Indiana Jones and the Fate of Atlantis intro
	// will sound like a bell if we use any delay here.
	// Bug #6242 "AUDIO: Built-In MT-32 MUNT Produces Wrong Sounds".
	_synth->setMIDIDelayMode(MT32Emu::MIDIDelayMode_IMMEDIATE);

	// We need to report the sample rate MUNT renders at as sample rate of our
	// AudioStream.
	_outputRate = _synth->getStereoOutputSampleRate();
	MidiDriver_Emulated::open();

	_initializing = false;

	if (screenFormat.bytesPerPixel > 1)
		g_system->fillScreen(screenFormat.RGBToColor(0, 0, 0));
	else
		g_system->fillScreen(0);

	g_system->updateScreen();

	_mixer->playStream(Audio::Mixer::kPlainSoundType, &_mixerSoundHandle, this, -1, Audio::Mixer::kMaxChannelVolume, 0, DisposeAfterUse::NO, true);

	return 0;
}