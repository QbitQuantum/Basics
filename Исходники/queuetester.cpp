int main(){
  char str[5][10]={
    "one", "two", "three", "four", "five"
  };
  char s[100];
  Queue q;
  int i;
  for(i=0;i<5;i++){
    q.add(str[i]);
  }

  while(!q.isEmpty()){
    q.remove(s);
    std::cout<<s<<std::endl;
  }

  return 0;
}