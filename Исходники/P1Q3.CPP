void main()
{
 clrscr();
 float A[100];int n,ch;
 cout<<"Enter the array elements::\n";
  cin>>n;

  enter(A,n);
  display(A,n);
  isort(A,n);
  lsearch(A,n);
getch();
}