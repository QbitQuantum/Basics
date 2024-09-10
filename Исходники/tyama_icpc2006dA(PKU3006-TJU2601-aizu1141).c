int main(){
  int a,d,n,c,x;
  createtable();
  for(;;){
    c=0;
    scanf("%d%d%d",&a,&d,&n);
    if(a==0)return 0;
    for(x=a;;x+=d){
      if(!table[x])c++;
      if(c==n){
        printf("%d\n",x);
        break;
      }
    }
  }
}