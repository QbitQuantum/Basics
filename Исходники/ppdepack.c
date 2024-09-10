static int test_pp(unsigned char *b)
{
	return memcmp(b, "PP20", 4) == 0;
}