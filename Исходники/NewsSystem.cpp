void NewsSystem_StartCore(void * lpParam){
	while(TRUE){
		NewsSystem.NewsCore();
	}
	_endthread();
}