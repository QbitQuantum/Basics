void C_thread::KillThread(){
   if(imp){
      RThread *thrd = (RThread*)imp;
      if(!thrd->ExitReason()){
         thrd->Terminate(1);
         thrd->Close();
      }
      delete thrd;
      imp = NULL;
   }
   status = STATUS_UNINITIALIZED;
}