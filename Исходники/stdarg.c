int main(int argc, char * argv[])
{
	int argi;
	long long loops = 1000000000;
	int do_vararg = 0;
	int do_fixarg = 0;
	int vals[10] = { 0,1,2,3,4,5,6,7,8,9 };

	for (argi = 1; argi < argc; argi++) {
		const char *word = argv[argi];
		if (word[0] != '-' || !word[1] || word[2])
			help(1);
		switch (word[1]) {
		case 'l':
			word = argv[++argi];
			loops = atoll(word);
			break;
		case 'v':
			do_vararg = 1;
			break;
		case 'a':
			do_fixarg = 1;
			break;
		default:
			help(1);
		}
	}

	if (do_vararg)
		TIME("vararg", run_vararg(loops,vals));
	if (do_fixarg)
		TIME("fixed", run_fixarg(loops,vals));

	return 0;
}