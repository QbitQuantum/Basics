void ui_gfx_init(running_machine &machine)
{
	ui_gfx_state *state = &ui_gfx;
	UINT8 rotate = machine.system().flags & ORIENTATION_MASK;

	// make sure we clean up after ourselves
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(FUNC(ui_gfx_exit), &machine));

	// initialize our global state
	memset(state, 0, sizeof(*state));

	// set up the palette state
	state->palette.columns = 16;

	// set up the graphics state
	for (UINT8 i = 0; i < MAX_GFX_DECODERS; i++)
		for (UINT8 j = 0; j < MAX_GFX_ELEMENTS; j++)
		{
			state->gfxdev[i].rotate[j] = rotate;
			state->gfxdev[i].columns[j] = 16;
		}

	// set up the tilemap state
	state->tilemap.rotate = rotate;
}