	/*
	 * See header file
	 */
	void new_impact(Input_t imp_input)
	{
		#ifdef DEBUG_IMPACT
		uint16_t i;
		pcSerial.printf("\t\tnew impact\n");
		#endif
		impact->starttime = imp_input.timestamp;
		impact->baseline = baseline;
		impact->sample_count = 0;
		impact->peak_count = 0;
		impact->max_amplitude = 0;
		// OPTION: don't reset arrays to zero.
		#ifdef DEBUG_IMPACT
		for ( i = 0; i < MAX_IMPACT_LENGTH; i++){
			impact->samples[i] = 0;
			impact->peaks[i].timestamp = 0;
			impact->peaks[i].value = 0;
		}
		#endif
	}