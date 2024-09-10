int main(int argc, char *argv[])
{
	return BindImageEx(BIND_NO_BOUND_IMPORTS | BIND_NO_UPDATE | BIND_ALL_IMAGES,
		argv[1], NULL, argv[2], StatusRoutine);	
}