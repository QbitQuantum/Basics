/*
	Load a binary image, return # bytes read.
*/
int  
data_load_binary(const char *type, const char *path, const char *filename,
				 u8 * loadat, int swap, int fileoffs, int imagesize, 
				 int maxsize)
{
	OSRef       ref;
	OSSize      size;
	OSError     err;
	OSSpec      spec;

	size = data_find_binary(path, filename, &spec);

	if (!size) {
		if (*filename) {
			command_logger(_L |LOG_USER|LOG_ERROR, 
						   _("Cannot find '%s' in path:\n'%s'\n"), 
						   filename, path);
		}
		return 0;
	}
	logger(_L|L_0, _("Loading %s image %s... "), type, OS_SpecToString1(&spec));

	if (imagesize)
		size = imagesize;
	else if (size - fileoffs > maxsize) {
		command_logger(_L | LOG_WARN | LOG_USER, _("%s too long, only %d bytes of %d read... "),
			 OS_SpecToString1(&spec), maxsize, size);
		size = maxsize - fileoffs;
	}

	if ((err = OS_Open(&spec, OSReadOnly, &ref)) != OS_NOERR) {
		OSerror(err, "\n");
		return 0;
	}

	if ((err = OS_Seek(ref, OSSeekAbs, fileoffs)) != OS_NOERR ||
		(err = OS_Read(ref, loadat, &size)) != OS_NOERR) {
		OSerror(err, _("could not read\n"));
		return 0;
	}

	if (swap) {
		logger(_L, _("swapping bytes... "));
		swab((const void *) loadat, (void *) loadat, size);
	}

	logger(_L| L_0, _("done\n"));

	OS_Close(ref);
	return size;
}