void reverse(char *s)
{
	char *word;
	word = strtok(s," ");
	while(word != NULL)
	{
		//printf("%s\n",word);
		strrev(word);
		printf("%s ",word);
		word = strtok(NULL, " ");
	}
	printf("\n");
	return;
}