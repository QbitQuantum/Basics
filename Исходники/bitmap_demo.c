int
main(int argc, char const *argv[])
{
	char bitmap[MAX_SIZE];
	memset(bitmap, 0, sizeof(bitmap));
	char *ptr = bitmap;
	int number_in = 0;
	int number_search = 0;
	int i = 0;

	printf("Please input the numbers continuously(less than and not equal %d) "
		"that will be saved in the bit map and enter the number -1 to finish!\n", 
		MAX_SIZE * sizeof(char) * 8);
	while(EOF != (scanf("%d", &number_in)))
	{
		if(-1 == number_in)
			break;

		ptr = bitmap;

		if(MAX_SIZE <= QUOTIENT(number_in))
			return 0;

		for (i = 0; i < QUOTIENT(number_in); ++i)
		{
			ptr++;
		}
		*ptr |= (0x01 << REMAINDER(number_in));
	}

	printf("Please input the numbers continuously(less than and not equal %d) "
		"that will be searched whether in the bit map or not and enter the number -1 to finish!\n", 
		MAX_SIZE * sizeof(char) * 8);
	while(EOF != (scanf("%d", &number_search)))
	{
		if(-1 == number_search)
			break;

		char location = (char)0;
		ptr = bitmap;

		if(MAX_SIZE < QUOTIENT(number_search))
			return 0;
		for (i = 0; i <= QUOTIENT(number_search); ++i)
		{		
			ptr++;
		}
		location = (*ptr) & (location | (0x01 << REMAINDER(number_search)));

		if(0 == location)
			printf("the number %d is not exist!\n", number_search);
		else
			printf("the number %d is exist!\n", number_search);
	}
	
	return 0;
}