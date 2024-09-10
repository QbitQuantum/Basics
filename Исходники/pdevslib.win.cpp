void spawnProcess(const char *path, char *arg) {
	spawnl(P_NOWAIT , path, " ", arg,NULL);;
}