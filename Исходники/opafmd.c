/**
 * Spawns an instance of the FM component.
 * 
 * @param instance Instance number the component belongs to 
 * @param component Integer representation of the component 
 *  				(1 = SM, 2 = FE)
 * @return int PID spawned or -1 if an error has occurred
 */
int spawn(const unsigned int instance, const int component){
	sigset_t mask;
	int *pids;
	int pid;
	char prog[32], name[32];
	if (instance >= FM_MAX_INSTANCES){
		fprintf(stderr, "Invalid instance number.\n");
		return -1;
	}
	if ((pids = componentToPIDArray(component)) == NULL){
		fprintf(stderr, "spawn: Invalid component number %d.\n", component);
		return -1;
	}
	if (pids[instance] != 0 && kill(pids[instance], 0) == 0){
		fprintf(stderr, "Instance %d of %s is already running.\n", instance, componentToString(component));
		return -1;
	}
	if (!config.instance[instance].component[component].enabled){
		fprintf(stderr, "Instance %d of %s is not enabled. Please enable instance in %s\n", instance, componentToString(component), FM_XML_CONFIG);
		return -1;
	}
	switch(pid = fork()){
	case 0:
		sigemptyset(&mask);
		sigaddset(&mask,SIGTERM);
		sigaddset(&mask,SIGCHLD);
		sigaddset(&mask,SIGHUP);
		sigprocmask(SIG_UNBLOCK, &mask, NULL);
		sprintf(prog, "/usr/lib/opa-fm/runtime/%s", componentToExecName(component));
		sprintf(name, "%s_%d", componentToExecName(component), instance);
		execle(prog, prog, "-e", name, NULL, nullEnv);
		break;
	case -1:
		fprintf(stderr, "Failed to start %s for instance %d.\n", componentToString(component), instance);
		break;
	default:
		fprintf(stdout, "Started instance %d of %s.\n", instance, componentToString(component));
		if(pid > 0) pids[instance] = pid;
		break;
	}
	return pid;
}