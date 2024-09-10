 static Thread* findThread(int thread_id) {
   for (int index = 0; index < threads->length(); index++) {
     Thread* thread = threads->at(index);
     if (thread == NULL) continue;
     if (thread->thread_id == thread_id)
       return thread;
   }
   return NULL;
 }