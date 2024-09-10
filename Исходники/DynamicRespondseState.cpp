void DynamicResponseState::execveCgiProgram(){
	char *emptylist[]={NULL};
	if(_fork()==0){
		setenv("QUERY_STRING",cgiArgs.c_str(),1);
		_dup2(getFileDescriptor(),STDOUT_FILENO);
		_execve(getFileName().c_str(),emptylist,environ);
	}
	_wait(NULL);
}