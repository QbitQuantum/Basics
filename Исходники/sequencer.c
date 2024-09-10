static void
run(LV2_Handle instance,
    uint32_t   sample_count)
{
	Sequencer* plugin = (Sequencer*)instance;

	/* Gate */
	const float* gate = plugin->gate;

	/* Step Trigger */
	const float* trigger = plugin->trigger;

	/* Loop Steps */
	const float loop_steps = *(plugin->loop_steps);

	/* Reset to Value on Gate Close */
	const float reset = *(plugin->reset);

	/* Value used when gate closed */
	float value_gate_closed = *(plugin->value_gate_closed);

	/* Step Values */
	float values[SEQUENCER_MAX_INPUTS];

	/* Output */
	float* output = plugin->output;

	float last_gate    = plugin->last_gate;
	float last_trigger = plugin->last_trigger;
	float last_value   = plugin->last_value;

	unsigned int  step_index = plugin->step_index;
	unsigned int  loop_index = LRINTF(loop_steps);
	int           rst        = reset > 0.0f;
	int           i;

	loop_index = loop_index == 0 ?  1 : loop_index;
	loop_index = (loop_index > SEQUENCER_MAX_INPUTS)
		? SEQUENCER_MAX_INPUTS
		: loop_index;

	for (i = 0; i < SEQUENCER_MAX_INPUTS; i++) {
		values[i] = *(plugin->values[i]);
	}

	for (uint32_t s = 0; s < sample_count; ++s) {
		if (gate[s] > 0.0f) {
			if (trigger[s] > 0.0f && !(last_trigger > 0.0f)) {
				if (last_gate > 0.0f) {
					step_index++;
					if (step_index >= loop_index) {
						step_index = 0;
					}
				} else {
					step_index = 0;
				}
			}

			output[s] = values[step_index];

			last_value = values[step_index];
		} else {
			if (rst) {
				output[s] = value_gate_closed;
			} else {
				output[s] = last_value;
			}

			step_index = 0;
		}
		last_gate    = gate[s];
		last_trigger = trigger[s];
	}

	plugin->last_gate    = last_gate;
	plugin->last_trigger = last_trigger;
	plugin->last_value   = last_value;
	plugin->step_index   = step_index;
}