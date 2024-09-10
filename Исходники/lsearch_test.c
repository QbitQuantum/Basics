int main(){int i,j,k,no,pow;
  for(i=0;i<SIZE;i++)
    ary[i]=i;
  for(i=0;i<100000;i++){
    pow=rand_r(&r_seed)%SIZE_B; 
    no = rand_r(&r_seed)%(1<<pow);
    if (!no) no=1;
    k=rand_r(&r_seed)%no;
    lsearch(&k,ary,no,sizeof(int),intcmp);
  }
  return 0;
}