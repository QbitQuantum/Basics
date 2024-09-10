void ui_gfx_init(running_machine &machine)
{
	ui_gfx_state *state = &ui_gfx;
	int gfx;

	/* make sure we clean up after ourselves */
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(ui_gfx_exit), &machine));

	/* initialize our global state */
	memset(state, 0, sizeof(*state));

	/* set up the palette state */
	state->palette.count = 16;

	/* set up the graphics state */
	for (gfx = 0; gfx < MAX_GFX_ELEMENTS; gfx++)
	{
		state->gfxset.rotate[gfx] = machine.system().flags & ORIENTATION_MASK;
		state->gfxset.count[gfx] = 16;
	}

	/* set up the tilemap state */
	state->tilemap.rotate = machine.system().flags & ORIENTATION_MASK;
}