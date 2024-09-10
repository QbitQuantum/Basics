v8Function TS_GetFileList(V8ARGS){
    v8::HandleScope TS_GetFileListscope;
	filehandle dir;
    filedata data;

	const char *directory;

	if(args.Length()>0){
			CHECK_ARG_STR(0);
		    v8::String::Utf8Value str(args[0]);


			if(strnlen(*str, 1022)<1){
				directory = "";
			}
			else{
				if(DEBUG) printf("[scriptfs] GetFileList Info: The relative directory was %s\n", *str);
				char * tdir = (char *)malloc(strlen(*str)+1);
				if(DEBUG) printf("[scriptfs] GetFileList Info: tdir = %s\n", tdir);
				tdir = strcat(tdir, *str);
                char * ls = strrchr(tdir, '/');
                if(ls[1]!='\0'){
                    strcat(tdir, "/");
                }
                if(DEBUG) printf("[scriptfs] GetFileList Info: The directory as concated was %s\n", tdir);

                directory = STRDUP(tdir);
                free(tdir);
			}
		}
	else{
		directory = "";
	}

    const char ** filenames = NULL;
	int i = 0;
	const char *fulldir = STRDUP((string(GetDirs()->save).append(directory)).c_str());
	if(DEBUG) printf("[scriptfs] GetFileList Info: The directory specified is %s\n", fulldir);
	#ifdef _WIN32

	const char *fulldirlist = STRDUP((string(GetDirs()->save).append(directory)+"*.*").c_str());
	DWORD attribs = ::GetFileAttributesA(fulldir);
	if ((attribs != INVALID_FILE_ATTRIBUTES) && (attribs & FILE_ATTRIBUTE_DIRECTORY)) {
		if(DEBUG) printf("[scriptfs] GetFileList Info: the directory was valid.");
		dir = FindFirstFile(fulldirlist, &data);

		if (dir!=INVALID_HANDLE_VALUE){
			do{
#else
	    if ((dir=opendir(GetDirs()->save))!=NULL){
	        while((data=readdir(dir))!=NULL){
#endif
				if((!ISDIRECTORY(data))&&(FILENAME(data)[0]!='.')){
					filenames = (const char **)realloc(filenames, (i+1)*sizeof(const char *));
					filenames[i] = STRDUP(FILENAME(data));
					i++;
				}
#ifdef _WIN32
		    } while(FindNextFile(dir, &data));
		    FindClose(dir);
		}//dir!=INVALID_HANDLE_VALUE
		free((void*)fulldirlist);
	}//attribs!=INVALID_FILE_ATTRIBUTES
#if DEBUG
	else{
		printf("[scriptfs] GetFileList Info: Directory does not exist.\n");
	}
#endif
#else
        }
        closedir(dir);
	}
#endif
	v8::Local<v8::Array> files = v8::Array::New(i);
	for(int e = 0; e<i; e++){
		files->Set(e, v8::String::New(filenames[e]));
        free((void*)filenames[e]);
	}
	free(filenames);
	free((void*)fulldir);
	if(directory!=NULL){
		free((void*)directory);
	}
	return TS_GetFileListscope.Close(files);

}