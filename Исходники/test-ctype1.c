static void
test_toascii (void)
{
	int i, j;
	for (i = -127; i < 256; )
		j = i, printf ("%s: %d -> %d\n", __FUNCTION__, j, toascii (i++));
}