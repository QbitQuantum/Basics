void PCRecorder::print() {
  if (counters == NULL) return;

  tty->cr();
  tty->print_cr("Printing compiled methods with PC buckets having more than %d ticks", ProfilerPCTickThreshold);
  tty->print_cr("===================================================================");
  tty->cr();

  GrowableArray<CodeBlob*>* candidates = new GrowableArray<CodeBlob*>(20);


  int s;
  {
    MutexLockerEx lm(CodeCache_lock, Mutex::_no_safepoint_check_flag);
    s = size();
  }

  for (int index = 0; index < s; index++) {
    int count = counters[index];
    if (count > ProfilerPCTickThreshold) {
      address pc = pc_for(index);
      CodeBlob* cb = CodeCache::find_blob_unsafe(pc);
      if (cb != NULL && candidates->find(cb) < 0) {
        candidates->push(cb);
      }
    }
  }
  for (int i = 0; i < candidates->length(); i++) {
    print_blobs(candidates->at(i));
  }
}