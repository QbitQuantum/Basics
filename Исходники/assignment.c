void del()
{
	struct employee current;
	FILE *search;
	FILE *mark;
	search=fopen("employees.dat", "rb");
	mark=fopen("employees.dat", "ab");
	int found=0;
	char input[6];
	
	printf ("\nPlease enter the number of the employee to be deleted.\n");
	scanf ("%5s", &input);
	flushall();
	
	fseek(search, HEADERSIZE, SEEK_SET);
	
	while(fread(&current, RECSIZE, 1, search)!=NULL && found==0)
	{
		if(strcmp(current.emp_num, input)==0)
		{
			found=1;
			mark=search;
		}
	}//end while
	
	if (found==0)
	{
		printf ("\nThe specified employee number does exist in the file.\n\n");
	}
	else
	{
		current.emp_num[0]='*';
		fwrite(&current, RECSIZE, 1, mark);
		update(0, 1);
	}
	
	fclose(search);
	fclose(mark);
}//end del()