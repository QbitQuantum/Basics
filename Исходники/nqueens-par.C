int main (int argc, char **argv) {
  int i, j, p, n;
  int total;
  char **maxBoard;
  char **initialBoard;
  unsigned int t1, t2, t3;

  MAIN_INITENV
  //Enforce arguments

  if (argc != 2) {
    printf("Usage: nqueens-seq <N>\nAborting.\n");
    exit(0);
  }
  gm = (GM*)G_MALLOC(sizeof(GM)); 
  gm->p = 8;
  gm->n = atoi(argv[1]); 
  n = gm->n;
  gm->total = 0;
  gm->maxBoard = (char**)G_MALLOC(n*sizeof(char*));
  gm->initialBoard = (char**)G_MALLOC(n*sizeof(char*));
  gm->global_max_profit = 0;

  for (i = 0; i < n; i++) {
    gm->maxBoard[i] = (char*)G_MALLOC(n*sizeof(char));
    gm->initialBoard[i] = (char*)G_MALLOC(n*sizeof(char));
    for (j = i; j < n; j++) {
      gm->maxBoard[i][j] = 0;
      gm->initialBoard[i][j] = 0;
    }
  }

  CLOCK(t1)
  for(i = 0; i < n; i++)
    CREATE(nqueens_wrapper)
  WAIT_FOR_END(n);
  CLOCK(t2)
  
  printf("Printing maximum profit board\n");
  printBoard(gm->maxBoard, gm->global_max_profit);
  CLOCK(t3)
  
  printf("Computation time: %u microseconds\n", t2-t1);
  printf("Printing time:    %u microseconds\n", t3-t2);
  MAIN_END
  return 0;
}