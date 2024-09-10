int main(int argc, char* argv[]) 
{
	int i, fd;

	for(i = 1; i < argc; ++i) 
	{
		fd = openfile(argv[i]);
		if(fd < 0) continue;
		printlines(fd, argv[i], argc);
		if(close(fd))
			perror("Close");
	}

	if(argc < 2)
	{
		fd = openfile("-");
		printlines(fd, "-", argc);
	}

	return 0;
}