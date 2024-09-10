		bool Delete(bool returnFalseOnRegistryRemovalFailure=false)
		{
			if(!*filename)
				return true; // guess it already didn't exist

			// remove read-only attribute so Windows will let us delete it
			// (our temporary files are read-only to discourage other apps from tampering)
			DWORD attributes = GetFileAttributes(filename);
			if(attributes & FILE_ATTRIBUTE_READONLY)
				SetFileAttributes(filename, attributes & ~FILE_ATTRIBUTE_READONLY);

			if(_unlink(filename) == 0 || errno != EACCES)
			{
				// remove it from our registry of files that need to be deleted, to reduce accumulation
				bool removed = TempFiles::RemoveEntryFromGarbageRegistry(filename);

				*filename = '\0';
				return removed || !returnFalseOnRegistryRemovalFailure; // successfully deleted or already didn't exist, return true unless registry removal failure notification was requested and that failed
			}

			// restore read-only if we couldn't delete it (not sure if this ever succeeds or matters though)
			if(attributes & FILE_ATTRIBUTE_READONLY)
				SetFileAttributes(filename, attributes);

			return false; // failed to delete read-only or in-use file
		}