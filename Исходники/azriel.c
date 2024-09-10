static void raiseDeadMoveToTopTarget()
{
	char c;
	int i, j;

	if (atTarget())
	{
		setEntityAnimation(self, "PHANTASMAL_BOLT_FIRE");

		self->thinkTime = 30;

		self->action = &raiseDead;

		self->mental = 2 + prand() % 4;

		STRNCPY(self->description, "123456", sizeof(self->description));

		for (i=0;i<6;i++)
		{
			j = prand() % 6;

			c = self->description[i];

			self->description[i] = self->description[j];

			self->description[j] = c;
		}
	}

	checkToMap(self);

	becomeTransparent();
}