/**
 *Set the first name
 *
 *Input:
 *	info	is a pointer to person's info
 *	name	contains the first name
 *Return:
 *	0 to indicate failure
 *	1 to indicate success
 */
int setFirstName(PersonInfo *info, char *name)
{
	if (name == NULL ) // Check for empty string
		{
			printf("No first name detected !");
			return 0; 
		}
	else
		{
			int i = 0;
			
			while( name[i] != '\0' ) // Count for the total number of characters in the string until end of the string
				i++ ;
				
			if  ( i > 20 ) // Check if the name has more than 20 characters, it will return 0
				{
					printf("Insufficient space to allocate your lengthy first name.I'm sorry !");
					return 0;
				}
			
			int j = 0 ;
			for (j = 0 ; name[j] != '\0' ; ) //Loop throughout the string 
			{
						
				if ( isalpha(name[j]) != 0 ) // If the current character is an alphabet, isalpha will return a value not equal to 0
						j++;				 // and increment the counter to check for next character
				
				else if ( isblank(name[j]) != 0 ) // Check for space in first name , isblank return not zero when true
					{
						if ( j == 0 )	// To check for the starting character of the name cannot be blank or space 
						{	
							printf("You can't have your first name starting with a blank");
							return 0;
						}
							
						else 
							j++;
					}
					
				else if ( isdigit(name[j]) != 0 ) //Check for presence of digits, isdigit will also return non zero value if true
					{
						printf("You have number/numbers in your first name @_@ ???");
						return 0;
					}
					
				else //If all the above condition aren't true, it will be characters liek @,_|\ and more....
					{
						printf("Invalid character found in your first name!");
						return 0;
					}
					
					
					
			}
					
			printf("Hello %s ",name); // Just to print out the first name
			return 1;	// Pass all the test and return 1 for success
				
		}
		
	
}