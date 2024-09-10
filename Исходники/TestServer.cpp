 static uint threadProc(void* data)
 {
   ThreadProc* threadData = (ThreadProc*)data;
   Socket socket;
   ASSERT(socket.open());
   ASSERT(socket.connect(Socket::loopbackAddr, 7266));
   Thread::sleep(42);
   threadData->sent = true;
   ASSERT(socket.send(threadData->testData, sizeof(threadData->testData)) == sizeof(threadData->testData));
   byte receiveData[100];
   ASSERT(socket.recv(receiveData, sizeof(receiveData)) == sizeof(receiveData));
   ASSERT(Memory::compare(&receiveData, &threadData->testData, sizeof(receiveData)) == 0);
   socket.close();
   return 32;
 }