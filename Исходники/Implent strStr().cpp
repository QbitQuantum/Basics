int main(){
  char* s1 = "334sacsld3";
  char* s2 = "sacs3";
  Solution s;
  char* result = s.strStr (s1,s2);
  if(result == NULL )
    cout << "NULL "<< endl;
  else
    cout << result << endl;
  getchar();
  return 0;
}