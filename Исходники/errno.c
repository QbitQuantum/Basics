/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret += _errno(argv[0]);
	return (ret == 0) ? 0 : 2;
}