/* Selectively delete a hierarchy */
int
delete_hierarchy(const char *dir, Boolean ign_err, Boolean nukedirs)
{
    char *cp1, *cp2;

    cp1 = cp2 = strdup(dir);
    if (!fexists(dir) && !issymlink(dir)) {
	if (!ign_err)
	    warnx("%s '%s' doesn't exist",
		isdir(dir) ? "directory" : "file", dir);
	return !ign_err;
    }
    else if (nukedirs) {
	if (vsystem("%s -r%s %s", REMOVE_CMD, (ign_err ? "f" : ""), dir))
	    return 1;
    }
    else if (isdir(dir) && !issymlink(dir)) {
	if (RMDIR(dir) && !ign_err)
	    return 1;
    }
    else {
	if (REMOVE(dir, ign_err))
	    return 1;
    }

    if (!nukedirs)
	return 0;
    while (cp2) {
	if ((cp2 = strrchr(cp1, '/')) != NULL)
	    *cp2 = '\0';
	if (!isemptydir(dir))
	    return 0;
	if (RMDIR(dir) && !ign_err) {
	    if (!fexists(dir))
		warnx("directory '%s' doesn't exist", dir);
	    else
		return 1;
	}
	/* back up the pathname one component */
	if (cp2) {
	    cp1 = strdup(dir);
	}
    }
    return 0;
}