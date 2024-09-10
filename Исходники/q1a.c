main()
{
	int *ptr;
	int no_els, no_bytes, i;
	
	printf ("Enter the number of elements.");
	scanf ("%d", &no_els);
	
	/*Calculating the number of bytes
	*/
	
	no_bytes=no_els;//sizeof(int) removed
	
	/*Allocating the memory
	*/
	
	ptr=(int*)malloc(no_bytes);
	
	if (ptr==NULL)
	{
		printf ("Cannot allocate memory.\n");
	}
	
	else
	{
		for (i=0;i<no_els;i++)
		{
			printf ("\nEnter element %d.\n", i);
			scanf ("%d", &*(ptr+i));
		}
	
		/*Display the number entered into the memory block
		*/
		
		for (i=0;i<no_els;i++)
		{
			printf ("\nElement %d is %d.\n", i, *(ptr+i));
		}
		
		free(ptr);
		
		flushall();
		getchar();
	}//end if
}//end main