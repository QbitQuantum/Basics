main()
{
    printf("Average from array of 5\n\n");
    int numbers[5];
    int size = 5;
	int average;
    int i;
    for(i=0;i<size;i++)
    {
        printf("Enter element: ");
        scanf("%d", &numbers[i]);
        printf("\n");
    }
        
	/*Call the function sum_array()*/
	average = my_array(numbers);
	printf("The average is %d", average);
    flushall();
    getchar();
}//end main