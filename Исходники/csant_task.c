/*
 * Make a directory, and all parent directories.
 */
static int Mkdir_P(const char *base, const char *dir)
{
      char *path = CSAntDirCombine(base, dir);
      char* slashpos = &path[strlen(base)];
      char* bslashpos;
      int retval = 0;
      char save;

      if(!path)
      {
		return errno;
      }
      while(*slashpos != '\0')
      {
		bslashpos = strchr(slashpos + 1, '\\');
		slashpos = strchr(slashpos + 1, '/');
		if (slashpos == 0 || (bslashpos != 0 && slashpos > bslashpos))
		  	slashpos = bslashpos;
		if (slashpos == 0)
		  	slashpos = strchr(path, '\0');
		save = *slashpos;
		*slashpos = '\0';
		retval = ILCreateDir(path);
		*slashpos = save;
		if (retval != IL_ERRNO_Success && retval != IL_ERRNO_EEXIST)
		  	break;
      }
      if(retval == IL_ERRNO_EEXIST)
		retval = IL_ERRNO_Success;
      ILFree(path);
      return retval;
}