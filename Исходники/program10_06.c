int main(void)
{
  char initial[3] = {' '};
  char name[80] = {' '};

  printf("Enter your first initial:  ");
  gets_s(initial, sizeof(initial));
  printf("Enter your name:  " );
  gets_s(name, sizeof(name));
  if(initial[0] != name[0])
    printf("%s, you got your initial wrong.\n", name);
  else
    printf("Hi, %s. Your initial is correct. Well done!\n", name);
  return 0;
}