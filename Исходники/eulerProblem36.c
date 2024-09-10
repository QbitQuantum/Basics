char* intToString(int number, int base){
  int count = 0;
  if(base == 10){
    char* str = calloc(8, sizeof(char));
    sprintf(str, "%d", number);
    return str;
  } else if (base == 2){
    char *temp = calloc(25, sizeof(char));
    bzero(temp, 25);
    while(number>0){
      int rem = number%2;
      char xe = intToChar(rem);
      strncat(temp, &xe, 1);
      count++;
      number/=2;
    }
    char* ret = reverse(temp);
    // free(temp);
    return ret;
  } else {
    printf("Could not convert to base %d\n", base);
  }
  return NULL;
}