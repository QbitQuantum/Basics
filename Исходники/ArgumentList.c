static void process_file(object list, char *file) 
{ 
	char buf[256], *p; 
	object fobj; 

	fobj = gOpenFile(File, file, "r"); 
	if (!fobj) { 
		vPrintf(stdoutStream, "Can't open %s\n", file); 
		exit(1); 
	} 
	while (gGets(fobj, buf, sizeof buf)) 
		for (p=buf ; *(p=process_token(p, list)) ; ); 
	gDispose(fobj); 
} 