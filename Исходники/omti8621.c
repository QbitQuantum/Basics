static void set_interrupt(const omti8621_state *state, enum line_state line_state) {
	if (state->irq_handler != NULL) {
		LOG2(("set_interrupt: status_port=%x", state->status_port));
		(*state->irq_handler)(&state->device->machine(), line_state);
	}
}