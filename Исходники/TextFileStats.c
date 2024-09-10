void countCharWordsSentCase(char fileName[], char fileName2[], int* charCount, int* wordCount, int* sentenceCount)
{
	//char c;
	char ch;
	FILE *fp1, *fp2;
	int no_of_char = 0, no_of_words = 1, no_of_sent = 0;
	fp1= fopen(fileName,"r");
	if( fp1 == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	fp2 = fopen(fileName2,"w");
	if( fp2 == NULL )
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	//upper to lower and viceversa
	while (!feof(fp1)) {
		no_of_char++;
		ch = fgetc(fp1);

		if (ch == ' ' || ch == '.' || ch == '\n' || ch == '\t')
		{
			if(ch == ' ' || ch == '\n' || ch == '\t')
			{
				fputc(ch,fp2);
				no_of_words++;
			}
			else
				if(ch == '.')
				{
					fputc(ch,fp2);
					no_of_sent++;
				}
		}

		else
			if (isalpha(ch))
			{
				if (isupper(ch))
				{
					fputc(tolower(ch),fp2);
				}
				else {
					fputc(toupper(ch),fp2);
				}
			}
			else
			{
				//fputc(' ',fp2);
			}
	}
	fclose(fp1);
	fclose(fp2);

	no_of_char--;
	*charCount = no_of_char;
	*wordCount = no_of_words;
	*sentenceCount = no_of_sent;

	return;

}