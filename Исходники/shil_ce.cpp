void ce_die(char* reason)
{
	if (reason)
		log("C.E. pass : die [%s]\n",reason);
	else
		log("C.E. pass : die\n");

	__debugbreak();
}