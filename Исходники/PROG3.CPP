void main()
{
 clrscr();
 float A[25],n;
 do
 {
   cout<<"Enter the no. of elements less than 25"<<endl;
     cin>>n;
 }while(n>25);
 input(A,n);
 display(A,n);
 isort(A,n);
 lsearch(A,n);
 getch();
}