int main(int arc, char **argv)
{
  int bufferSize = atoi(argv[1]);
  int numProducers = atoi(argv[2]);
  int numConsumers = atoi(argv[3]);
  int amountProduced = atoi(argv[4]);

  printf("Buffer size = %d, ", bufferSize);
  printf("number of producer threads = %d, ", numProducers);
  printf("number of consumer threads = %d, ", numConsumers);
  printf("and each producer produces %d\n", amountProduced);

  int *buffer;
  buffer = malloc(bufferSize*sizeof(int));
  buffer[0] = 1;

//  HANDLE producers[1];
//  HANDLE consumers[1];
  HANDLE *producers;
  HANDLE *consumers;
  producers = malloc(numProducers*sizeof(HANDLE));
  consumers = malloc(numConsumers*sizeof(HANDLE));

  full = CreateSemaphore(
		  NULL,
		  0,
		  bufferSize,
		  NULL);
  empty = CreateSemaphore(
		  NULL,
		  bufferSize,
		  bufferSize,
		  NULL);

//  PINFO pInfo[1];
//  CINFO cInfo[1];
  PINFO *pInfo;
  CINFO *cInfo;
  pInfo = malloc(numProducers*sizeof(PINFO));
  cInfo = malloc(numConsumers*sizeof(CINFO));

  for(int i=0; i<numProducers; i++) {
    pInfo[i] = (PINFO)HeapAlloc(GetProcessHeap(),
		    HEAP_ZERO_MEMORY,
		    sizeof(pinfo));
  }
  for(int i=0; i<numConsumers; i++) {
    cInfo[i] = (CINFO)HeapAlloc(GetProcessHeap(),
		    HEAP_ZERO_MEMORY,
		    sizeof(cinfo));
  }

  for(int i=0; i<numProducers; i++) {
    pInfo[i]->threadNumber = i+1;
    pInfo[i]->counter = 0;
    pInfo[i]->toProduce = amountProduced;
    pInfo[i]->buff = buffer;
    pInfo[i]->bufferSize = bufferSize;
  }
  for(int i=0; i<numConsumers; i++) {
    cInfo[i]->threadNumber = i+1;
    cInfo[i]->toConsume = (numProducers * amountProduced) / numConsumers;
    cInfo[i]->buff = buffer;
    cInfo[i]->bufferSize = bufferSize;
  }
  int remainder = (numProducers*amountProduced)%numConsumers;
  for(int i=0; i<remainder; i++) {
    cInfo[i]->toConsume++;
  }
//
  for(int i=0; i<numProducers; i++) {
    producers[i] = CreateThread(NULL,
		    		0,
				producerFunc,
				pInfo[i],
				0,
				NULL);
  }
  for(int i=0; i<numConsumers; i++) {
    consumers[i] = CreateThread(NULL,
		    		0,
				consumerFunc,
				cInfo[i],
				0,
				NULL);
  }

  WaitForMultipleObjects(numProducers, producers, TRUE, INFINITE);
  WaitForMultipleObjects(numConsumers, consumers, TRUE, INFINITE);

  CloseHandle(full);
  CloseHandle(empty);
  CloseHandle(mutex);

  printf("***All jobs finished***\n");
}