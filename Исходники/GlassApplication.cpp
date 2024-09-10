 ENTER_MAIN_THREAD()
 {
     GetEnv()->CallVoidMethod(runnable, javaIDs.Runnable.run);
     CheckAndClearException(GetEnv());
 }