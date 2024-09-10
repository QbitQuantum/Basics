int main(int argc, char *argv[])
{
  int k, i, j, x, y; 
  int A[5][5];
  seq seq1 = {o, a, a, a, b, a};
  seq seq2 = {o, b, a, a, b, a};

  if(argc != 2 || (sscanf(argv[1], "%d", &k)) != 1) {
    printf("\tBitte Syntax beachten: ./afg41 <Substringlaenge>\n");
    exit(EXIT_FAILURE);
  }

  printf("\n");
  for(i = 1; i <= 6 - k; i++){
    for(j = 1; j <= 6 - k; j++){
      printf("\tmc(");
      for(x = k; x > 0; x--) {
	printf("%c", seq1[i+(k-x)]);
	if(x == 1) {
	  printf(", ");
	}
      }
      for(y = k; y > 0; y--) {
      printf("%c", seq2[j+(k-y)]);
	if(y == 1) {
	  printf(")\n");
	}
      }
    }
  }
  
  

  for(j = 0; j < 6; j++) {
    printf("\n");
    for(i = 0; i < 6; i++) {
      if((i == 0) || (j == 0)) {
	A[i][j] = 0;
      } else {
	A[i][j] = A[i-1][j-1];
	if(seq1[i] == seq2[j]) {
	  A[i][j] += 1;
	}
      }
      printf("\t%d", A[i][j]);
    }
  }
  printf("\n\n");
  for(i = 1; i <= 6 - k; i++){
    for(j = 1; j <= 6 - k; j++){
      printf("\tmc(");
      for(x = k; x > 0; x--) {
	printf("%c", seq1[i+(k-x)]);
	if(x == 1) {
	  printf(", ");
	}
      }
      for(y = k; y > 0; y--) {
      printf("%c", seq2[j+(k-y)]);
	if(y == 1) {
	  printf(") = %d\n", (A[i+(k-1)][j+(k-1)] - A[i-1][j-1]));
	}
      }
    }
  }
  printf("\n");
  return(EXIT_SUCCESS);
}