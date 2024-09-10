void POSIXSaveFileManager::checkPath(const Common::FSNode &dir) {
	const Common::String path = dir.getPath();
	clearError();

	struct stat sb;

	// Check whether the dir exists
	if (stat(path.c_str(), &sb) == -1) {
		// The dir does not exist, or stat failed for some other reason.
		// If the problem was that the path pointed to nothing, try
		// to create the dir (ENOENT case).
		switch (errno) {
		case EACCES:
			setError(Common::kWritePermissionDenied, "Search or write permission denied: "+path);
			break;
		case ELOOP:
			setError(Common::kUnknownError, "Too many symbolic links encountered while traversing the path: "+path);
			break;
		case ENAMETOOLONG:
			setError(Common::kUnknownError, "The path name is too long: "+path);
			break;
		case ENOENT:
			if (mkdir(path.c_str(), 0755) != 0) {
				// mkdir could fail for various reasons: The parent dir doesn't exist,
				// or is not writeable, the path could be completly bogus, etc.
				warning("mkdir for '%s' failed", path.c_str());
				perror("mkdir");

				switch (errno) {
				case EACCES:
					setError(Common::kWritePermissionDenied, "Search or write permission denied: "+path);
					break;
				case EMLINK:
					setError(Common::kUnknownError, "The link count of the parent directory would exceed {LINK_MAX}: "+path);
					break;
				case ELOOP:
					setError(Common::kUnknownError, "Too many symbolic links encountered while traversing the path: "+path);
					break;
				case ENAMETOOLONG:
					setError(Common::kUnknownError, "The path name is too long: "+path);
					break;
				case ENOENT:
					setError(Common::kPathDoesNotExist, "A component of the path does not exist, or the path is an empty string: "+path);
					break;
				case ENOTDIR:
					setError(Common::kPathDoesNotExist, "A component of the path prefix is not a directory: "+path);
					break;
				case EROFS:
					setError(Common::kWritePermissionDenied, "The parent directory resides on a read-only file system:"+path);
					break;
				}
			}
			break;
		case ENOTDIR:
			setError(Common::kPathDoesNotExist, "A component of the path prefix is not a directory: "+path);
			break;
		}
	} else {
		// So stat() succeeded. But is the path actually pointing to a directory?
		if (!S_ISDIR(sb.st_mode)) {
			setError(Common::kPathDoesNotExist, "The given savepath is not a directory: "+path);
		}
	}
}