void main()
{
    clrscr();
    char c[10][40];
    int n;
    do
    {
        cout<<"Enter the no. of countries you want to enter (<10) : ";
        cin>>n;
    } while(n>10);
    enter(c,n);
    display(c,n);
    sort(c,n);
    lsearch(c,n);
    getch();
}