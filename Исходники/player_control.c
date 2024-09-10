struct player_control *
pc_new(unsigned buffer_chunks, unsigned int buffered_before_play)
{
	struct player_control *pc = g_new0(struct player_control, 1);

	pc->buffer_chunks = buffer_chunks;
	pc->buffered_before_play = buffered_before_play;

	pc->mutex = g_mutex_new();
	pc->cond = g_cond_new();

	pc->command = PLAYER_COMMAND_NONE;
	pc->error_type = PLAYER_ERROR_NONE;
	pc->state = PLAYER_STATE_STOP;
	pc->cross_fade_seconds = 0;
	pc->mixramp_db = 0;
	pc->mixramp_delay_seconds = nanf("");

	return pc;
}