int GBASamples::build_sample(uint32_t pointer)
{	// Do nothing if sample already exists
	for (int i=samples_list.size()-1; i >= 0; --i)
		if (samples_list[i] == pointer) return i;

	// Read sample data
	if (fseek(inGBA, pointer, SEEK_SET)) throw -1;

	struct
	{
		uint32_t loop;
		uint32_t pitch;
		uint32_t loop_pos;
		uint32_t len;
	}
	hdr;
	fread(&hdr, 4, 4, inGBA);

	//Now we should make sure the data is coherent, and reject
	//the samples if errors are suspected

	//Detect invalid samples
	bool loop_en;
    bool bdpcm_en = false;

	if (hdr.loop == 0x40000000)
		loop_en = true;
	else if (hdr.loop == 0x00000000)
		loop_en = false;
	else if (hdr.loop == 0x1)
	{
		bdpcm_en = true;    // Detect compressed samples
	    loop_en = false;
	}
	else
		throw -1;			// Invalid loop -> return error

	// Compute SF2 base note and fine tune from GBA pitch
	// GBA pitch is 1024 * Mid_C frequency
	double delta_note = 12 * log2(sf2->default_sample_rate * 1024.0 / hdr.pitch);
	double int_delta_note = round(delta_note);
	unsigned int pitch_correction = int((int_delta_note - delta_note) * 100);
	unsigned int original_pitch = 60 + (int)int_delta_note;

	// Detect Golden Sun samples
	if (goldensun_synth && hdr.len == 0 && hdr.loop_pos == 0)
	{
		if (fgetc(inGBA) != 0x80) throw -1;
		uint8_t type = fgetc(inGBA);
		switch (type)
		{
			case 0:		// Square wave
			{
				std::string name = "Square @0x" + hex(pointer);
				uint8_t duty_cycle = fgetc(inGBA);
				uint8_t change_speed = fgetc(inGBA);
				if (change_speed == 0)
				{	// Square wave with constant duty cycle
					unsigned int base_pointer = 128 + 64 * (duty_cycle >> 2);
					sf2->add_new_sample(goldensun_synth, UNSIGNED_8, name.c_str(), base_pointer, 64, true, 0, original_pitch, pitch_correction);
				}
				else
				{	// Sqaure wave with variable duty cycle, not exact, but sounds close enough
					sf2->add_new_sample(goldensun_synth, UNSIGNED_8, name.c_str(), 128, 8192, true, 0, original_pitch, pitch_correction);
				}
			}	break;

			case 1:		// Saw wave
			{
				std::string name = "Saw @0x" + hex(pointer);
				sf2->add_new_sample(goldensun_synth, UNSIGNED_8, name.c_str(), 0, 64, true, 0, original_pitch, pitch_correction);
			}	break;

			case 2:		// Triangle wave
			{
				std::string name = "Triangle @0x" + hex(pointer);
				sf2->add_new_sample(goldensun_synth, UNSIGNED_8, name.c_str(), 64, 64, true, 0, original_pitch, pitch_correction);
			}	break;

			default :
				throw -1;
		}