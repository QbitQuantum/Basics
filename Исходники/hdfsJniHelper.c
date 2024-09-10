/**
 * getJNIEnv: A helper function to get the JNIEnv* for the given thread.
 * If no JVM exists, then one will be created. JVM command line arguments
 * are obtained from the LIBHDFS_OPTS environment variable.
 *
 * @param: None.
 * @return The JNIEnv* corresponding to the thread.
 */
JNIEnv* getJNIEnv(void)
{

    const jsize vmBufLength = 1;
    JavaVM* vmBuf[vmBufLength]; 
    JNIEnv *env;
    jint rv = 0; 
    jint noVMs = 0;

    // Only the first thread should create the JVM. The other trheads should
    // just use the JVM created by the first thread.
    LOCK_JVM_MUTEX();

    rv = JNI_GetCreatedJavaVMs(&(vmBuf[0]), vmBufLength, &noVMs);
    if (rv != 0) {
        fprintf(stderr, "JNI_GetCreatedJavaVMs failed with error: %d\n", rv);
        UNLOCK_JVM_MUTEX();
        return NULL;
    }

    if (noVMs == 0) {
        //Get the environment variables for initializing the JVM
        char *hadoopClassPath = getenv("CLASSPATH");
        if (hadoopClassPath == NULL) {
            fprintf(stderr, "Environment variable CLASSPATH not set!\n");
            UNLOCK_JVM_MUTEX();
            return NULL;
        } 
        char *hadoopClassPathVMArg = "-Djava.class.path=";
        size_t optHadoopClassPathLen = strlen(hadoopClassPath) + 
          strlen(hadoopClassPathVMArg) + 1;
        char *optHadoopClassPath = malloc(sizeof(char)*optHadoopClassPathLen);
        snprintf(optHadoopClassPath, optHadoopClassPathLen,
                "%s%s", hadoopClassPathVMArg, hadoopClassPath);

        int noArgs = 1;
        //determine how many arguments were passed as LIBHDFS_OPTS env var
        char *hadoopJvmArgs = getenv("LIBHDFS_OPTS");
        char jvmArgDelims[] = " ";
        if (hadoopJvmArgs != NULL)  {
                char hadoopJvmArgs_cpy[strlen(hadoopJvmArgs)+1];
                strcpy(hadoopJvmArgs_cpy, hadoopJvmArgs);
                char *result = NULL;
                result = strtok( hadoopJvmArgs, jvmArgDelims );
                result = strtok( hadoopJvmArgs_cpy, jvmArgDelims );
                while ( result != NULL ) {
                        noArgs++;
        		result = strtok( NULL, jvmArgDelims);
           	}
        }
        JavaVMOption options[noArgs];
        options[0].optionString = optHadoopClassPath;
		//fill in any specified arguments
	if (hadoopJvmArgs != NULL)  {
            char hadoopJvmArgs_cpy[strlen(hadoopJvmArgs)+1];
            strcpy(hadoopJvmArgs_cpy, hadoopJvmArgs);
            char *result = NULL;
            result = strtok( hadoopJvmArgs_cpy, jvmArgDelims );
            int argNum = 1;
            for (;argNum < noArgs ; argNum++) {
                options[argNum].optionString = result; //optHadoopArg;
                result = strtok( NULL, jvmArgDelims);
            }
        }

        //Create the VM
        JavaVMInitArgs vm_args;
        JavaVM *vm;
        vm_args.version = JNI_VERSION_1_2;
        vm_args.options = options;
        vm_args.nOptions = noArgs; 
        vm_args.ignoreUnrecognized = 1;

        rv = JNI_CreateJavaVM(&vm, (void*)&env, &vm_args);
        if (rv != 0) {
            fprintf(stderr, "Call to JNI_CreateJavaVM failed "
                    "with error: %d\n", rv);
            UNLOCK_JVM_MUTEX();
            return NULL;
        }

        free(optHadoopClassPath);
    }
    else {
        //Attach this thread to the VM
        JavaVM* vm = vmBuf[0];
        rv = (*vm)->AttachCurrentThread(vm, (void*)&env, 0);
        if (rv != 0) {
            fprintf(stderr, "Call to AttachCurrentThread "
                    "failed with error: %d\n", rv);
            UNLOCK_JVM_MUTEX();
            return NULL;
        }
    }
    UNLOCK_JVM_MUTEX();

    return env;
}