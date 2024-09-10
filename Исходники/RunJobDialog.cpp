 virtual void Run(OperationEnvironment &env) {
   env.SetText(_T("Working..."));
   env.SetProgressRange(30);
   for (unsigned i = 0; i < 30 && !env.IsCancelled(); ++i) {
     env.SetProgressPosition(i);
     env.Sleep(500);
   }
 }