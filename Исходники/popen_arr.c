static int popen2_impl(FILE** in, FILE** out,  const char* program, const char* const argv[], const char* const envp[], int lookup_path) {
    
	int child_stdout = -1;
	int child_stdin = -1;
	
	int to_be_written = -1;
	int to_be_read = -1;
	
	if(in) {
	    int p[2]={-1,-1}; 
	    int ret = pipe(p);
	    if(ret!=0) { return -1; }
	    to_be_written=p[1];
	    child_stdin =p[0];
	    *in = fdopen(to_be_written, "w");
	    if (*in == NULL) {
	        close(to_be_written);
	        close(child_stdin);
	        return -1;
	    }
	}
	if(out) {
	    int p[2]={-1,-1};
	    int ret = pipe(p);
	    if(ret!=0) {
	        if (in) {
	           close(child_stdin);
	           fclose(*in);
	           *in = NULL;
	        }
	        return -1;
	    }
	    to_be_read   =p[0];
	    child_stdout=p[1];
	    *out = fdopen(to_be_read, "r");
	}
	
	
	int childpid = fork();
	if(!childpid) {
	   if(child_stdout!=-1) {
	       close(to_be_read);
	       dup2(child_stdout, 1);
	       close(child_stdout);
	   }
	   if(child_stdin!=-1) {
	       close(to_be_written);
	       dup2(child_stdin, 0);
	       close(child_stdin);
	   }
	   if (lookup_path) {
	       if (envp) {
	           execvpe(program, (char**)argv, (char**)envp);
	       } else {
	           execvp (program, (char**)argv);
	       }
	   } else {
	       if (envp) {
	           execve(program, (char**)argv, (char**)envp);
	       } else {
	           execv (program, (char**)argv);
	       }
	   }
	   _exit(ENOSYS);
	}
	
    if(child_stdout!=-1) {
        close(child_stdout);
    }
    if(child_stdin!=-1) {
        close(child_stdin);
    }
    
    return childpid;
}