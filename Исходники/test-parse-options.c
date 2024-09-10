static int number_callback(const struct option *opt, const char *arg, int unset)
{
	*(int *)opt->value = strtol(arg, NULL, 10);
	return 0;
}