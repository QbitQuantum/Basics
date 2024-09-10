int main()
{
	char word[] = "The litle girl go to school";

	cout << word << endl;
		
	char *wPtr = strtok( word, " " );
	

	while ( wPtr != NULL )
	{
		//cout << *( wPtr + 1 ) << endl;
		printLatinWord( wPtr );
		wPtr = strtok( NULL, " " );
	}
		
	cout << endl;

	return 0;
}