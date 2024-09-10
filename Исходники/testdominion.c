static void recordTransitions(Node *queue) {
  FILE *fp = Fopen(FILE_NAME, "w");
  fprintf(fp, "***beginning of testdominon transitions***\n");

  // record states
  struct gameState *oldState = Dequeue(queue, &queue);
  while (queue != NULL && queue != NULL) {
    // record transition from old state to new state
    struct gameState *newState = Dequeue(queue, &queue);
    debug(fp, oldState, newState);

    // clean-up and update old state
    Free(oldState);
    oldState = newState;
  }

  fprintf(fp, "***end of testdominon transitions***\n");

  // clean-up old state and file
  Free(oldState);
  Fclose(fp);
}