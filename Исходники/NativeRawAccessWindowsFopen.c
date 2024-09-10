JNIEXPORT void JNICALL 
Java_xxl_core_io_raw_NativeRawAccess_open(JNIEnv *env, jobject obj, jstring jfilename) {
	FILE *jfilep; 			// int of the file/device
	jlong sectors;
	fpos_t length;
	// BOOL isDevice=FALSE;
	const jbyte *filename;		// Java needs UTF-coded strings, c needs ASCII
	jint sectorSize;
	
	DEBUG_OUTPUT("Enter open",0);
	init(env, obj);
	
	// do not call get methods before init!
	jfilep = (FILE*) getfilep(env, obj);
	sectorSize = getsectorSize(env, obj);
	// Converts utf to ASCII
	filename = (*env)->GetStringUTFChars(env, jfilename, NULL);
	// got it?
	
	if (filename==NULL) {
		reportError(env,obj,"Filename NULL");
		return;
	}
	
	// Already a device open?
	if (jfilep!=0) {
		reportError(env,obj,"File already open");
		return;
	}

  	DEBUG_OUTPUT("Filename: %s",filename);
  	
  	//if ( (filename[0]=='\\') && (filename[1]=='\\') && (filename[2]=='.') && (filename[3]=='\\') )
  	//	isDevice=TRUE;
  		
	jfilep = fopen(filename,"rwbc");

	// Open failed?
	if (jfilep==NULL) {
		reportError(env,obj,"Open failed - file not found");
		return;
	}

	// Set the int inside the java object
	setfilep(env, obj, (jlong) jfilep);
  	DEBUG_OUTPUT("Filepointer: %d",(long) jfilep);

	setbuf(jfilep, NULL);

	if (fseek(jfilep,0,SEEK_END)!=0) {
		reportError(env,obj,"seek failed");
		return;
	}

	fgetpos(jfilep,&length);
	if (length==-1) {
		reportError(env,obj,"Size returned 0");
		return;
	}
	else  
		sectors = length/sectorSize;
		
  	DEBUG_OUTPUT("Sektoren: %d\n", (long) sectors);
	setsectors(env, obj, (jlong) sectors);
}