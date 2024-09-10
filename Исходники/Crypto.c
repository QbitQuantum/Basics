int getAnswer(int n, int p)
{
  long double  k = 2;
  int val = powl(k,(long double)(p-1)/2)%p;
  printf("%d",val);
  
  printf("%d",k);
  long double x = powl((k + sqrt(k^2-n)),(p+1)/2);
  return (int)x;
}