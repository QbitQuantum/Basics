FILE *
setup(int line)
{
	FILE	*f;
	int	r;

	if ((f = fopen(filename, "r+")) == NULL)
		err(2, "fopen");
	if ((r = fwide(f, 0)) != 0)
		fail(line, r, "==", "fopen");
	return (f);
}