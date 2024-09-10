// The actual callback from the connection point arrives here
STDMETHODIMP EventProxy::Invoke(DISPID dispID, REFIID riid,
    LCID lcid, unsigned short wFlags, DISPPARAMS *pDispParams,
    VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
  	const char 	*eventMethodName = NULL; //Sourceforge report 1394001 
  	JNIEnv      *env = NULL;

  // map dispID to jmethodID
  for(int i=0;i<MethNum;i++) 
  {
    if (MethID[i] == dispID) { 
		USES_CONVERSION;
		eventMethodName = W2A((OLECHAR *)MethName[i]);
    	}
  }
  // added 1.12
  if (!eventMethodName) {
  	// just bail if can't find signature.  no need to attach
	// printf("Invoke: didn't find method name for dispatch id %d\n",dispID);
   	return S_OK;
  }
  if (DISPATCH_METHOD & wFlags) 
  {
        
    // attach to the current running thread
	//printf("Invoke: Attaching to current thread using JNI Version 1.2\n");
		JavaVMAttachArgs attachmentArgs; 
        attachmentArgs.version = JNI_VERSION_1_2;  
        attachmentArgs.name = NULL; 
        attachmentArgs.group = NULL; 
        jvm->AttachCurrentThread((void **)&env, &attachmentArgs); 
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}

	if (!eventMethodName) 
  	{
	    // could not find this signature in list
  		// printf("Invoke: didn't find method name for dispatch id %d\n",dispID);
  		// this probably leaves a native thread attached to the vm when we don't want it
  		ThrowComFail(env, "Event method received was not defined as part of callback interface", -1);
  		
  		// should we detatch before returning?? We probably never get here if we ThrowComFail()
	    // jvm->DetachCurrentThread();
    	return S_OK;
	  }

	// find the class of the InvocationHandler
   	jclass javaSinkClass = env->GetObjectClass(javaSinkObj);
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}
	//printf("Invoke: Got sink class\n");
    jmethodID invokeMethod;
    invokeMethod = env->GetMethodID(javaSinkClass, "invoke", "(Ljava/lang/String;[Lcom/jacob/com/Variant;)Lcom/jacob/com/Variant;");
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}
    jstring eventMethodNameAsString = env->NewStringUTF(eventMethodName);
	//printf("Invoke: Got method name\n");
	// now do what we need for the variant
    jmethodID getVariantMethod = env->GetMethodID(javaSinkClass, "getVariant", "()Lcom/jacob/com/Variant;");
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}
	//printf("Invoke: Found way too getVariant\n");
    jobject aVariantObj = env->CallObjectMethod(javaSinkObj, getVariantMethod); 
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}
	//printf("Invoke: Made Variant\n");
   	jclass variantClass = env->GetObjectClass(aVariantObj);
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}

	// create the variant parameter array
    // how many params
    int numVariantParams = pDispParams->cArgs;
    // make an array of them
    jobjectArray varr = env->NewObjectArray(numVariantParams, variantClass, 0);
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}
	//printf("Invoke: Created Array\n");
    int i,j;
    for(i=numVariantParams-1,j=0;i>=0;i--,j++) 
    {
      // construct a java variant holder
	  jobject arg = env->CallObjectMethod(javaSinkObj, getVariantMethod); 
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}
      // get the empty variant from it
      VARIANT *va = extractVariant(env, arg);
      // copy the value
      VariantCopy(va, &pDispParams->rgvarg[i]);
      // put it in the array
      env->SetObjectArrayElement(varr, j, arg);
	  env->DeleteLocalRef(arg);
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}
    }
	//printf("Invoke: Filled Array\n");
    // Set up the return value
    jobject ret;

    ret = env->CallObjectMethod(javaSinkObj, invokeMethod, 
		eventMethodNameAsString, varr); 
	//printf("Invoke: Invoked callback\n");
    if (!env->ExceptionOccurred() && ret != NULL) {
        VariantCopy(pVarResult, extractVariant(env,ret));
    }
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}
	// don't need the first variant we created to get the class
	// SF 1689061 change not accepted but put in as comment for later reminder
    //Java_com_jacob_com_Variant_release(env, aVariantObj);
	env->DeleteLocalRef(aVariantObj);
		if (env->ExceptionOccurred()) { env->ExceptionDescribe(); env->ExceptionClear();}

    // Begin code from Jiffie team that copies parameters back from java to COM
    for(i=numVariantParams-1,j=0;i>=0;i--,j++) 
    {
		jobject arg = env->GetObjectArrayElement(varr, j);
		VARIANT *java = extractVariant(env, arg);
		VARIANT *com = &pDispParams->rgvarg[i];
		convertJavaVariant(java, com);
		// SF 1689061 change not accepted but put in as comment for later reminder
		//Java_com_jacob_com_Variant_release(env, arg);
		zeroVariant(env, arg);
		env->DeleteLocalRef(arg);
    }
    // End code from Jiffie team that copies parameters back from java to COM
    // detach from thread
	//printf("Invoke: Detatching\n");
	jvm->DetachCurrentThread();
  	//fflush(stdout);
    return S_OK;
  }
  return E_NOINTERFACE;
}