/*
 * CheckArea()
 *
 * This function deals with the question of whether the given string is a
 * directory and to create it if possible and needed.
 */
char CheckArea(MenuId id, char c, char *drive, char *dir_x)
{
    char work[100];

    switch (c) {
    case IS_DIR:
	return TRUE;
    case NO_IDEA:
	if (strLen(dir_x) != 0) {
	    sprintf(work, "%s does not exist. Create it", dir_x);
	    if (SysopGetYesNo(id, "", work)) {
		DoBdos(SETDISK, toUpper(*drive) - 'A');
		if (mkdir(dir_x) == BAD_DIR) {
		    SysopPrintf(id, "?ERROR CREATING!");
		    homeSpace();
		    return FALSE;
		}
		else {
		    homeSpace();
		    return TRUE;
		}
	    }
	}
	else {
	    return TRUE;
	}
	return FALSE;
    default:
	SysopPrintf(id, "That's not a directory!\n ");
	return FALSE;
    }
}