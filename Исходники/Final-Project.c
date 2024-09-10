int main()
{
	system ("title ");
	system("color f0");
	char nextcheque, compname[50], name[50];	
	int randNo;	
	
	do
   	{	
	  system ("cls");
    	  printmessage (); // function call
	  srand (time (NULL));
	  randNo = 100000 + rand () % (1000000-100000+1); // generate random numbers
	  printcheque (compname, randNo, name); // function call
	  printf ("\n\n\n");
	  printf ("Anymore cheque? > ");
	  fflush (stdin);
	  scanf ("%c", &nextcheque);
	  printf ("\n");
	}
	
	while (nextcheque == 'Y' || nextcheque == 'y');
	
	printf ("Thank you for your cooperation.\n\n");		
	system("pause"); 
	return 0;
}