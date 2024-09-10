int do_decompress(u8 *input, int len, u8 *output, void (*error)(char *x))
{
	return decompress(input, len, NULL, NULL, output, NULL, error);
}