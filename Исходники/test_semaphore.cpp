 Body(int nThread_, int nIter_, semaphore &mySem_,
         vector<int>& ourCounts_,
         vector<double>& tottime_
         ) : nThreads(nThread_), nIters(nIter_), mySem(mySem_), ourCounts(ourCounts_), tottime(tottime_) { sBarrier.initialize(nThread_); pCount = 0; }