int main(int argc, const char **argv) {

	/*Check for args*/
	if (argc != 3) {
		fprintf(stderr, "USAGE: index <inverted-index file name> "
						"<directory or file name>\n");
		return 1;
	}
	if (argv[2][0] == ')') {
			/*Don't allow from root directory*/
			fprintf(stderr,"ERROR: Indexing from root is disallowed!\n");
			return EXIT_FAILURE;
	}
	wordList = SLCreate(compareWords);
	/*Check if arg2 is directory or file*/
	struct stat s;
	if( stat(argv[2],&s) == 0 ) {
		if( s.st_mode & S_IFDIR ) {
			/*Directory*/
			char *dir;
			dir = (char *) malloc ( BUFSIZ );
			snprintf(dir, BUFSIZ-1, "%s", argv[2]);
			
			openAndIndexDirectory(dir);
			free (dir);
		}
		else if( s.st_mode & S_IFREG ) {
			/*File*/
			char *file;
			file = (char *) malloc ( BUFSIZ );
			snprintf(file, BUFSIZ-1, "%s", argv[2]);
						
			openAndIndexFile(file);
			free (file);
		}
		else {
			/*Don't know what it is*/
			fprintf(stderr,"STAT: Unknown data type\n");
			return EXIT_FAILURE;
		}
	}
	else {
		fprintf(stderr,"STAT: Unknown fatal error (Check file/dir name)\n");
		return EXIT_FAILURE;
	}
	/*Write inverted index to specified file*/
	writeWordListToFile(argv[1]);
	/*Destroy word list*/
	destroyWordList();
	


}