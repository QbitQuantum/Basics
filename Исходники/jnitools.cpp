 JNIAttach::JNIAttach(JNIEnv* env)
 {
   if (!ThreadJNI.get())
     ThreadJNI.reset(new JNIHandle);
   if (env)
   {
     assert(!ThreadJNI->env || env == ThreadJNI->env);
     JVM(env);
     ThreadJNI->env = env;
   }
   else if (!ThreadJNI->env)
   {
     JavaVM* jvm = JVM();
     assert(jvm);
     if (jvm->GetEnv((void**)&ThreadJNI->env, QI_JNI_MIN_VERSION) != JNI_OK ||
         ThreadJNI->env == 0)
     {
       char threadName[] = "qimessaging-thread";
       JavaVMAttachArgs args = { JNI_VERSION_1_6, threadName, 0 };
       if (JVM()->AttachCurrentThread((envPtr)&ThreadJNI->env, &args) != JNI_OK ||
           ThreadJNI->env == 0)
       {
         qiLogError() << "Cannot attach callback thread to Java VM";
         throw std::runtime_error("Cannot attach callback thread to Java VM");
       }
       ThreadJNI->attached = true;
     }
   }
   ++ThreadJNI->lockCount;
 }