int main(){
  int t,i,j,k,a;
  scanf("%d",&t);
  while(t--){
    scanf("%d",&a);
    scanf("%s",b);
    if( a==0 ){
      printf("%s\n",b);
      continue;
    }
    j = Remainder(a);
    printf("%d\n",gcd(a,j));
  }
  return 0;
}