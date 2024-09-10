int main(int argc, char *argv[])
{
ParseArguments(argc, argv);//incorrect arguments? print help & exit. Also, fill in SourceDirectoryName and DestinationDirectoryName; process flags.
Vprintf("OddBackup, version %s.\nBackup '%s' to '%s'.\n", VERSION, SourceDirectoryName, DestinationDirectoryName);
switch (Suspicion)
	{
	case 1: Vprintf("All attempts of shell-injections will be eliminated!\n");break;
	case 0: Vprintf("You'll be asked about fixing suspicious filenames.\n");break;
	case -1: Vprintf("You won't be disturbed with suspicious filenames. Enjoy your day!\n");break;
	}
struct dirent * DirectoryEntryPointer;
DIR * ProcessingDirPointer;

PushDir(SourceDirectoryName);

while (ProcessingDirectoryName = PopDir())
	{
	if (DotsCheck(ProcessingDirectoryName))//eliminate "." and ".." entries
		{
		continue;
		}
	if (!TryDirectory(ProcessingDirectoryName))
		{
		printf("Can't backup %s.\n", ProcessingDirectoryName);
		continue;
		}
	Dprintf("Processing %s\n", ProcessingDirectoryName);
	Vprintf("Entering %s\n", ProcessingDirectoryName);
	ProcessingDirPointer = opendir(ProcessingDirectoryName);
	CATCH_ERROR("Can't open directory");
	while ((DirectoryEntryPointer = readdir(ProcessingDirPointer)) != NULL)
		{
		switch(DirectoryEntryPointer->d_type)
			{
			case DT_DIR :	PushDir(AbsoluteSourceName(DirectoryEntryPointer->d_name)); break;//it's a directory - will be processed too
			case DT_REG :	if (IsToBeBackuped(DirectoryEntryPointer->d_name))//it's a file
						{
						BackupAndGzip(DirectoryEntryPointer->d_name);
						};
					break;
			default : printf("%s is neither file nor directory - can't backup.\n", DirectoryEntryPointer->d_name);
			}
		}
	Vprintf("Leaving %s\n", ProcessingDirectoryName);
	closedir(ProcessingDirPointer);
	free(ProcessingDirectoryName);
	}

return 0;
}