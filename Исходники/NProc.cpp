 bool terminate(NProc* np){
   mutex_.readLock();
   
   auto itr = stateMap_.find(np);
   if(itr == stateMap_.end()){
     mutex_.unlock();
     return true;
   }
   
   State* s = itr->second;
   mutex_.unlock();
   
   return s->terminate();
 }