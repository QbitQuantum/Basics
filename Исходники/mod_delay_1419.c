static void runAddingModDelay(LADSPA_Handle instance, unsigned long sample_count) {
	ModDelay *plugin_data = (ModDelay *)instance;
	LADSPA_Data run_adding_gain = plugin_data->run_adding_gain;

	/* Base delay (s) (float value) */
	const LADSPA_Data base = *(plugin_data->base);

	/* Delay (s) (array of floats of length sample_count) */
	const LADSPA_Data * const delay = plugin_data->delay;

	/* Input (array of floats of length sample_count) */
	const LADSPA_Data * const input = plugin_data->input;

	/* Output (array of floats of length sample_count) */
	LADSPA_Data * const output = plugin_data->output;
	LADSPA_Data * buffer = plugin_data->buffer;
	unsigned int buffer_mask = plugin_data->buffer_mask;
	float fs = plugin_data->fs;
	unsigned int write_ptr = plugin_data->write_ptr;

#line 42 "mod_delay_1419.xml"
	unsigned long pos;

	for (pos = 0; pos < sample_count; pos++) {
	  float tmp;
	  const float rpf = modff((base + delay[pos]) * fs, &tmp);
	  const int rp = write_ptr - 4 - f_round(tmp);

	  buffer[write_ptr++] = input[pos];
	  write_ptr &= buffer_mask;

	  buffer_write(output[pos], cube_interp(rpf, buffer[(rp - 1) & buffer_mask], buffer[rp & buffer_mask],  buffer[(rp + 1) & buffer_mask], buffer[(rp + 2) & buffer_mask]));
	}
	plugin_data->write_ptr = write_ptr;
}