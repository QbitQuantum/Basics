void gottlieb_knocker(running_machine &machine)
{
	device_t *samples = space->machine().device("samples");
	if (!strcmp(machine.system().name,"reactor"))	/* reactor */
	{
	}
	else if (samples != NULL)	/* qbert */
		sample_start(samples, 0,44,0);
}