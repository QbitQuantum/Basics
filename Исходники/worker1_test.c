int main(int argc, char** argv) {
  int worker_limit, browser_limit;
  srand(98769876);

  pthread_t workers[8];

  char *mutex_name = tempnam(0,"worker1.");
  mutex_sem = sem_open(mutex_name+4,O_CREAT,0777,1);
  if(!mutex_sem) {
    perror("No mutex!\n");
    exit(1);
  }

  /* TEST 1: several short-duration workers, one browser */
  init();
  for(int i=0;i<8;i++) {
    randomize();
    worker_limit = 120;
    pthread_create(&workers[i],0,worker_thread,(void*)&worker_limit);	 
  }

  pthread_t browsers[100];
  browser_limit = 960;
  pthread_create(&browsers[0],0,browser_thread,(void*)&browser_limit);
  void *result;
  pthread_join(browsers[0],&result);

  for(int i=0;i<8;i++) 
    pthread_join(workers[i],&result);

  if(pairs==960)
    printf("[PASS] worker1: short-duration workers, one browser.\n");
  else
    printf("[FAIL] worker1: insufficient pairs %d != 960\n",pairs);

  worker_count=0; 
  browser_count=0;
  pairs = 0;
  /* TEST 2: several medium-duration workers, several browsers */
  init();
  for(int i=0;i<8;i++) {
    randomize();
    worker_limit = 2000;
    pthread_create(&workers[i],0,worker_thread,(void*)&worker_limit);	 
  }

  browser_limit = 800;
  for(int i=0;i<20;i++) 
    pthread_create(&browsers[i],0,browser_thread,(void*)&browser_limit);


  for(int i=0;i<20;i++) 
    pthread_join(browsers[i],&result);

  for(int i=0;i<8;i++) 
    pthread_join(workers[i],&result);

  if(pairs==16000) 
    printf("[PASS] worker1: medium-duration workers, 20 browsers.\n");
  else
    printf("[FAIL] warker1: insufficient pairs, %d != 16000\n",pairs);

  worker_count=0; 
  browser_count=0;
  pairs = 0;
  /* TEST 3: one worker, several browsers */
  init();
  for(int i=0;i<1;i++) {
    randomize();
    worker_limit = 2000;
    pthread_create(&workers[i],0,worker_thread,(void*)&worker_limit);	 
  }

  browser_limit = 100;
  for(int i=0;i<20;i++) 
    pthread_create(&browsers[i],0,browser_thread,(void*)&browser_limit);	


  for(int i=0;i<20;i++) 
    pthread_join(browsers[i],&result);

  for(int i=0;i<1;i++) 
    pthread_join(workers[i],&result);

  if(pairs==2000)
    printf("[PASS] worker1: 1 worker, 20 browsers.\n");
  else
    printf("[FAIL] warker1: insufficient pairs, %d != 2000\n",pairs);
}