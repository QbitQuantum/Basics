static void cleanup_p(int argc, const char **argv)
{
	RETURN_IF_NULL(if_hh);

	EXECV(if_hh->cleanup);
}