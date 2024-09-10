 virtual void
 run (Arg)
   {
     ulong l1 (rand() % 1000);
     ulong l2 (rand() % 1000);
     string s1 (randStr(50));
     string s2 (randStr(50));
     const char* cp (s1.c_str());
     
     verifyWrapper<ulong> (l1, l2);
     verifyWrapper<ulong&> (l1, l2);
     verifyWrapper<ulong*> (&l1, &l2);
     verifyWrapper<ulong*> ((0), &l2);
     verifyWrapper<ulong*> (&l1, (0));
     verifyWrapper<ulong const&> (l1, l2);
     
     verifyWrapper<string> (s1, s2);
     verifyWrapper<string&> (s1, s2);
     verifyWrapper<string*> (&s1, &s2);
     
     verifyWrapper<const char*> (cp, "Lumiera");
     
     
     verifySaneInstanceHandling();
     verifySaneMoveHandling();
     verifyWrappedRef ();
     
     verifyFunctionResult ();
     verifyFunctionRefResult ();
   }