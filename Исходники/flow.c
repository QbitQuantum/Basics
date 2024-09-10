pid_t forkLisp(any ex) {
   pid_t n;
   int i, hear[2], tell[2];
   static int mic[2];

   flushAll();
   if (!Spkr) {
      if (pipe(mic) < 0)
         pipeError(ex, "open");
      closeOnExec(ex, mic[0]), closeOnExec(ex, mic[1]);
      Spkr = mic[0];
   }
   if (pipe(hear) < 0  ||  pipe(tell) < 0)
      pipeError(ex, "open");
   closeOnExec(ex, hear[0]), closeOnExec(ex, hear[1]);
   closeOnExec(ex, tell[0]), closeOnExec(ex, tell[1]);
   for (i = 0; i < Children; ++i)
      if (!Child[i].pid)
         break;
   if ((n = fork()) < 0)
      err(ex, NULL, "fork");
   if (n == 0) {
      void *p;

      Slot = i;
      Spkr = 0;
      Mic = mic[1];
      close(hear[1]), close(tell[0]), close(mic[0]);
      if (Hear)
         close(Hear),  closeInFile(Hear),  closeOutFile(Hear);
      initInFile(Hear = hear[0], NULL);
      if (Tell)
         close(Tell);
      Tell = tell[1];
      for (i = 0; i < Children; ++i)
         if (Child[i].pid)
            close(Child[i].hear), close(Child[i].tell),  free(Child[i].buf);
      Children = 0,  free(Child),  Child = NULL;
      for (p = Env.inFrames; p; p = ((inFrame*)p)->link)
         ((inFrame*)p)->pid = 0;
      for (p = Env.outFrames; p; p = ((outFrame*)p)->link)
         ((outFrame*)p)->pid = 0;
      for (p = CatchPtr; p; p = ((catchFrame*)p)->link)
         ((catchFrame*)p)->fin = Zero;
      free(Termio),  Termio = NULL;
      if (Repl)
         ++Repl;
      val(PPid) = val(Pid);
      val(Pid) = boxCnt(getpid());
      run(val(Fork));
      val(Fork) = Nil;
      return 0;
   }
   if (i == Children)
      allocChildren();
   close(hear[0]), close(tell[1]);
   Child[i].pid = n;
   Child[i].hear = tell[0];
   nonblocking(Child[i].tell = hear[1]);
   Child[i].ofs = Child[i].cnt = 0;
   Child[i].buf = NULL;
   return n;
}