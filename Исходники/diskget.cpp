int main(int argc, char** argv)
{

	int filetype;
	int size;
	int startblock;
	int blocksize;
	char *name = new char[DIRECTORY_MAX_NAME_LENGTH];
	FILE *fp;

	if (argv[2] == 0){
		printf("File not found\n");
		free(name);
		return 0;
	}

	if ((fp=fopen(argv[1],"r")))
	{
		currentFile = getRootDirStart(fp)*512;

		while (1){
			fseek(fp, currentFile,SEEK_SET);
			filetype = getFileType(fp);
			if (filetype == 3){
				//printf("F ");
			} else if (filetype == 5){
				//printf("D ");
			} else {
				printf("File not found\n");
				break;
			}
			size = getSize(fp);
			startblock = getStartBlock(fp);
			blocksize = getBlockSize(fp);
			printf("%d\n",blocksize);
			getName(fp,name);
			currentFile+=64;
			if (strcmp(argv[2],name) == 0){
				//printf("found!\n");
				copyFile(fp,startblock,size,name);
				break;
			}
		}
	} else
		printf("File not found\n");
	free(name);
	fclose(fp);
	return 0;
}