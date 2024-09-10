static void respawn()
{
	self->thinkTime--;

	if (self->thinkTime % 3 == 0)
	{
		self->flags ^= NO_DRAW;
	}

	if (self->thinkTime <= 0)
	{
		self->flags &= ~NO_DRAW;

		self->touch = &pushEntity;

		self->mental = 0;

		self->action = &horizontalGlassWait;

		self->thinkTime = self->maxThinkTime;

		self->active = FALSE;

		STRNCPY(self->requires, self->objectiveName, sizeof(self->requires));
	}
}