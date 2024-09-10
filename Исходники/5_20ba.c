int main(){

  printf("\n");
  printf("***Allows for const qualifier and function arguments.\n");
  printf("***Checks most errors I could think of.\n");
  printf("\n");

  while (gettoken() != EOF){
    out[0] = name[0] = '\0';
    error = 0;

    if (pdatatype() == -1){
      printf("Error: expression needs to begin with a valid return type\n");
      while ( getchar() != '\n')
	;
      continue;
    }
    dcl();
    if (error == 1){
      error = 0;
      while (getchar() != '\n')
	;
      continue;
    }
    if (name[0] == '\0'){
      printf("Error: no valid variable/function name in declaration.\n");
      continue;
    }

    if (tokentype != '\n')
      printf("Error: syntax error\n");
    printf("%s: %s %s\n", name, out, datatype);

  }

  return 0;
}