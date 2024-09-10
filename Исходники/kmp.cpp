int main () {
  Solution s;

  char * s1 ;
  char * s2 ;
  char * s3;
  s1 = (char *)malloc(100000);
  s2 = (char *)malloc(10000);
  strcpy(s1,"aaabcabcabcd");
  strcpy(s2,"abcabcabcd");
  s3 = s.strStr(s1,s2);
  string ss(s3);
  cout<<ss<<endl;
}