void input(struct product *pro,int n,int i)
 {
   char num[10];
   if(i==n)return;
   head();
   flushall();
   printf("\n\n\n    Product # %d",i+1);
   do
   {
   printf("\n\n\n Enter Product Name : ");
   gets(pro->name);
   }while(alpha(pro->name)==0);
   do
   {
   printf("\n Enter Price : ");
   gets(num);
   }while(digit(num)==0);
   pro->price=atoi(num);

   input(pro+1,n,i+1);
 }