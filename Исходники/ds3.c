main()
{
     int i,d[MAX],n,k;
     printf("Enter elements into the array: ");
     for(i=0;i<10;i++)
     {
         scanf("%d",&d[i]);
     }
     printf("Enter the number to search: ");
     scanf("%d",&n);
     k=lsearch(d,0,10,n);
     if(k==1)
           printf("Item %d found at index: %d",n,k);
     if(k=-1)
           printf("Item %d was not found.",n);
     printf("\nTotal number of comparisons done: %d",c);
     
}