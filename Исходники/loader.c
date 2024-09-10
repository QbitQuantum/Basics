char *
load_file(char *filename)
{
	long file_handle;
	char *file;
	struct xattr file_info;
	
	if(Fxattr(0,filename,&file_info)==0)
	{
		file_handle=Fopen(filename,16);
		file=(char *)malloc(file_info.size);
		Fread(file_handle,file_info.size,file);
		Fclose(file_handle);
	}
	else
	{
		file=strdup("<html><head><title>Page not found</title></head><body><h1>Page not found</h1></body></html>");
	}
	return(file);
}