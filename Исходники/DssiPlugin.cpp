static void startGUI(const char *directory, const char *dllName, const char *label,
	                 const char *oscUrl, const char *instanceTag)
{
    DBG (oscUrl);

    struct dirent *entry;
    char *dllBase = strdup(dllName);
    char *subpath;
    DIR *subdir;
    char *filename;
    struct stat buf;
    int fuzzy;

    if (strlen(dllBase) > 3 &&
        !strcasecmp(dllBase + strlen(dllBase) - 3, ".so"))
    {
        dllBase[strlen(dllBase) - 3] = '\0';
    }

    if (*dllBase == '/') {
        subpath = dllBase;
        dllBase = strdup(strrchr(subpath, '/') + 1);
    } else {
    	subpath = (char *)malloc(strlen(directory) + strlen(dllBase) + 2);
	    sprintf(subpath, "%s/%s", directory, dllBase);
    }

    for (fuzzy = 0; fuzzy <= 1; ++fuzzy) {

	if (!(subdir = opendir(subpath))) {
		fprintf(stderr, "%s: can't open plugin GUI directory \"%s\"\n", label, subpath);
	    free(subpath);
	    free(dllBase);
	    return;
	}

	while ((entry = readdir(subdir))) {
	    
	    if (entry->d_name[0] == '.') continue;
	    if (!strchr(entry->d_name, '_')) continue;

	    if (fuzzy) {
		    fprintf(stderr, "checking %s against %s\n", entry->d_name, dllBase);
            if (strlen(entry->d_name) <= strlen(dllBase) ||
                strncmp(entry->d_name, dllBase, strlen(dllBase)) ||
                entry->d_name[strlen(dllBase)] != '_')
                continue;
	    } else {
		    fprintf(stderr, "checking %s against %s\n", entry->d_name, label);
            if (strlen(entry->d_name) <= strlen(label) ||
                strncmp(entry->d_name, label, strlen(label)) ||
                entry->d_name[strlen(label)] != '_')
                continue;
	    }
	    
	    filename = (char *)malloc(strlen(subpath) + strlen(entry->d_name) + 2);
	    sprintf(filename, "%s/%s", subpath, entry->d_name);
	    
	    if (stat(filename, &buf)) {
		    perror("stat failed");
		    free(filename);
		    continue;
	    }
	    
	    if ((S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode)) &&
    		(buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
 		{
		    fprintf(stderr, "%s: trying to execute GUI at \"%s\"\n", label, filename);
		
		    if (fork() == 0) {
		        execlp(filename, filename, oscUrl, dllName, label, instanceTag, NULL);
		        perror("exec failed");
		        exit(1);
		    }
		
		    free(filename);
		    free(subpath);
		    free(dllBase);
		    return;
	    }
	    
	    free(filename);
	}
    }

	fprintf(stderr, "no GUI found for plugin \"%s\" in \"%s/\"\n", label, subpath);
    free(subpath);
    free(dllBase);
}