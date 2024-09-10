int main()
{
    int i, j;
    long k;
    char buffer[] = {'0', '1','2','3','4','5','6','7','8','9'};

    time_t t1, t2;

    clrscr();

    time (&t1);

    for (i = 0; i < 10; i++)
	printf("%c", buffer[i]);
    puts("");

    for (j = 0; j < 10; j++)
    {
	RotateBufRight(buffer, &buffer[10], j);
	for (i = 0; i < 10; i++)
	    printf("%c", buffer[i]);
	puts("");
    }

    
    time(&t2);
    printf("\n%f\n", difftime(t2, t1));

    getch();puts("\n\n");
    
    clrscr();

    
    for (j = 0; j < 10; j++)
    {
	RotateBufLeft(buffer, &buffer[10], j);
        for (i = 0; i < 10; i++)
            printf("%c", buffer[i]);
        puts("");
    }
  
    puts("\n\n");
  
    SwapBuffer(&buffer[0], &buffer[5], 5);
    for (i = 0; i < 10; i++)
            printf("%c", buffer[i]);
        puts("");
   puts("\n\n");
   
   SwapBuffer(&buffer[0], &buffer[5], 5);
   for (i = 0; i < 10; i++)
            printf("%c", buffer[i]);
        puts("");
        puts("\n\n");
  
   RotateBufLeft(&buffer[0], &buffer[10], 2);

 
   
   SlowSwapBufferParts(&buffer[1],  &buffer[5], &buffer[7], &buffer[9]);
   for (i = 0; i < 10; i++)
            printf("%c", buffer[i]);
        puts("");
      
   SwapBufferParts(&buffer[1],  &buffer[5], &buffer[7], &buffer[9]);
   for (i = 0; i < 10; i++)
            printf("%c", buffer[i]);
        puts("");

    
}