void main()
{
clrscr();
/*int a[3][3],b[3][3],c[3][3];
int i,j;
for(i=0;i<3;i++)
for(j=0;j<3;j++)
a[i][j]=i;

for(i=0;i<3;i++)
for(j=0;j<3;j++)
b[i][j]=i;
matrixmultiplication(a,b,c);
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
cout<<c[i][j]<<"\t";
cout<<"\n";
}
*/
int ac[3][1],bc[3][1];
cout<<"enter the first x coordinate: ";
cin>>ac[1][1];
cout<<"enter the first y coordinate: ";
cin>>ac[2][1];
ac[3][1]=1;

cout<<"\n\nenter the second x coordinate: ";
cin>>bc[1][1];
cout<<"enter the second y coordinate: ";
cin>>bc[2][1];
bc[3][1]=1;


float o;
int r[3][3];
int fc[3][1];
cout<<"enter the rotation angle: ";
cin>>o;
rotationmatrix(o,r);
matrixmultiplication(r,bc,fc);
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:/tc/bgi");
linedda(ac[1][1],ac[2][1],bc[1][1],bc[2][1]);
linedda(ac[1][1],ac[2][1],fc[1][1],fc[2][1]);
getch();
}