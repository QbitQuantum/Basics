 BusyBodyScoped( int nThread_, int workRatiox100_, tbb::enumerable_thread_specific<double> &locals_, int &unprotected_count_, bool test_throw_) :
     locals(locals_),
     nThread(nThread_),
     WorkRatiox100(workRatiox100_),
     unprotected_count(unprotected_count_),
     test_throw(test_throw_) {
     sBarrier.initialize(nThread_);
 }