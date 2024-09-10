void main()
{
 int array[size],i,s,ele,ans;
 char choice;
 do
  {
   clrscr();
   printf("\n\n\tEnter the size of the array : ");
   scanf("%d",&s);
   if(s>size)
    {
     printf("\n\n\t\tOverflow Error");
     printf("\n\t\tPress any key to continue");
     choice='n';
     getch();
    }
   else
    {
     printf("\n\n\tEnter the elements of the array ");
     for(i=0;i<s;i++)
      {
       printf(": ");
       scanf("%d",&array[i]);
       printf("\t\t\t\t\t");
      }
     printf("\n\n\tEnter the element to be searched : ");
     scanf("%d",&ele);
     ans=lsearch(ele,s,array);
     if(ans==0)
      printf("\n\n\n\tThe array does not consists of the element %d",ele);
     else
      printf("\n\n\n\tThe array consists of the element %d",ele);
    }
   printf("\n\n\n\n\t\tWant to continue (y/n) : ");
   scanf("%s",&choice);
  }while(choice=='y'||choice=='Y');
 getch();
}