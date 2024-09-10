static void fill_random(running_machine &machine, UINT8 *base, UINT32 length)
{
	while (length--)
		*base++ = machine.rand();
}