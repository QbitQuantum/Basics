int main(int argc, char *argv[]) {
  wq.size = 0;
  wq.head = NULL;
  wq.tail = NULL;
  wq.push_wait = &push_wait;
  wq.peek = &peek;
  wq.pop = &pop;

  rq.size = 0;
  rq.head = NULL;
  rq.tail = NULL;
  rq.push_exponential = &push_exponential;
  rq.peek = &peek;
  rq.pop = &pop;

  dq.size = 0;
  dq.head = NULL;
  dq.tail = NULL;
  dq.push_wait = &push_wait;
  dq.peek = &peek;
  dq.pop = &pop;
  node_counter = 0;


  FILE *file = fopen(argv[1], "r");
  fseek(file, 0, SEEK_END);
  long fsize = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *string  =malloc(fsize+1);
  fread(string, fsize, 1, file);
  fclose(file);

  string[fsize] = 0;

  //add stuff to node -> waiting queue
  char *token, *saveptr,*saveptr2, *temp, *ptr_end;
  int j, k, a;
  for(j = 0; ; j++, string = NULL){
    token = strtok_r(string, "\n", &saveptr);
    if (token == NULL) {
      break;
    }
    //get current time + x
    struct timeval tv;
    //printf("current%d", time);

    Node *n = (Node*)malloc(sizeof(Node));
    n->name = malloc(11);

    for (k = 0; ; k++, token = NULL){
      temp = strtok_r(token, "\' \', \t", &saveptr2);
      if (temp == NULL) {
        break;
      }
      if(k == 0) {
        strcpy(n->name, temp);
      }
      else if(k == 1) {
        a = atoi(temp);
        n->start_time = a;
      }
      else if(k == 2) {
        a = atoi(temp);
        n->cpu_time = a * 1000;
      }
      else {
        a = atoi(temp);
        n->io_count = a;
        n->io_blocks_left = trunc((n->io_count + 8191) / 8192);
        //printf("io blocks left = %d+8191 div 8192 = %d", n->io_count, n->io_blocks_left);
        n->priority = 1;
        n->cpu_completed= 0;
        n->io_block_time = n->cpu_time / n->io_blocks_left;
        n->io_block_next = n->io_block_time;
        //printf("\nblock time: %d", n->io_blocks_left);
        n->time_slice = 10;
        wq.push_wait(&wq, n);
        node_counter++;
      }
    }
  }

  // wait for things to go down
  pthread_t waiting;
  pthread_t ready;
  pthread_t finished;
  if (pthread_create(&waiting, NULL, &exponentialHold, NULL)){
    printf("Could not create thread \n");
  }
  if (pthread_create(&ready, NULL, &exponentialReady, NULL)) {
    printf("Could not create thread \n");
  }
  if (pthread_create(&finished, NULL, &done_queue, NULL)) {
    printf("Could not create thread \n");
  }
  if(pthread_join(waiting, NULL)){
    printf("Could not join thread\n");
  }
  if(pthread_join(ready, NULL)) {
    printf("Could not join thread\n");
  }
  if(pthread_join(finished, NULL)) {
    printf("Could not join thread\n");
  }

  //printf("%s", dq.head->name);
  //pop
  //run
  //cpu_time != compl_time?  push(ready)
  return 0;

}