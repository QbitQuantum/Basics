static void kTermWriteFile(char *name)
{
	FILE f;
	unsigned char buffer[512] = "Let's write a file";
	f=openFile(name,'w');
	if(f.flags == FS_FILE_INVALID){
		print("\r\nFile not found...");
		closeFile(&f);
		return;
	} else if (f.flags== FS_DIRECTORY){
		print("\r\n%s is a directory");
		closeFile(&f);
		return;
	}

	if(writeFile(&f,buffer,19) > 0)
		print("Writing complete\r\n");

	closeFile(&f);
}