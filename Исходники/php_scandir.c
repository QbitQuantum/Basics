PHPAPI int php_scandir(const char *dirname, struct dirent **namelist[], int (*selector) (const struct dirent *entry), int (*compare) (const struct dirent **a, const struct dirent **b))
{
	DIR *dirp = NULL;
	struct dirent **vector = NULL;
	int vector_size = 0;
	int nfiles = 0;
	char entry[sizeof(struct dirent)+MAXPATHLEN];
	struct dirent *dp = (struct dirent *)&entry;

	if (namelist == NULL) {
		return -1;
	}

	if (!(dirp = opendir(dirname))) {
		return -1;
	}

	while (!php_readdir_r(dirp, (struct dirent *)entry, &dp) && dp) {
		int dsize = 0;
		struct dirent *newdp = NULL;

		if (selector && (*selector)(dp) == 0) {
			continue;
		}

		if (nfiles == vector_size) {
			struct dirent **newv;
			if (vector_size == 0) {
				vector_size = 10;
			} else { 
				vector_size *= 2;
			}

			newv = (struct dirent **) realloc (vector, vector_size * sizeof (struct dirent *));
			if (!newv) {
				return -1;
			}
			vector = newv;
		}

		dsize = sizeof (struct dirent) + ((strlen(dp->d_name) + 1) * sizeof(char));
		newdp = (struct dirent *) malloc(dsize);

		if (newdp == NULL) {
			goto fail;
		}

		vector[nfiles++] = (struct dirent *) memcpy(newdp, dp, dsize);
	}

	closedir(dirp);

	*namelist = vector;

	if (compare) {
		qsort (*namelist, nfiles, sizeof(struct dirent *), compare);
	}

	return nfiles;

fail:
	while (nfiles-- > 0) {
		free(vector[nfiles]);
	}
	free(vector);
	return -1;	
}