static void test_mmap_wrong_magic_keyset (const char * tmpFile)
{
	// first write a mmap file
	{
		Key * parentKey = keyNew (TEST_ROOT_KEY, KEY_VALUE, tmpFile, KEY_END);
		KeySet * conf = ksNew (0, KS_END);
		PLUGIN_OPEN ("mmapstorage");

		KeySet * ks = simpleTestKeySet ();
		succeed_if (plugin->kdbSet (plugin, ks, parentKey) == 1, "kdbSet was not successful");

		keyDel (parentKey);
		ksDel (ks);
		PLUGIN_CLOSE ();
	}

	// now manipulate magic keyset inside the mapped region
	FILE * fp;
	if ((fp = fopen (tmpFile, "r+")) == 0)
	{
		yield_error ("fopen() error");
	}
	struct stat sbuf;
	if (stat (tmpFile, &sbuf) == -1)
	{
		yield_error ("stat() error");
	}

	int fd = fileno (fp);
	char * mappedRegion = mmap (0, sbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (mappedRegion == MAP_FAILED)
	{
		ELEKTRA_LOG_WARNING ("error mapping file %s\nmmapSize: " ELEKTRA_STAT_ST_SIZE_F, tmpFile, sbuf.st_size);
		yield_error ("mmap() error");
		return;
	}
	if (fp)
	{
		fclose (fp);
	}

	KeySet * magicKs = (KeySet *) (mappedRegion + sizeof (MmapHeader));
	magicKs->size = 1234; // magic keyset contains SIZE_MAX here

	if (msync ((void *) mappedRegion, sbuf.st_size, MS_SYNC) != 0)
	{
		yield_error ("msync() error");
		return;
	}

	if (munmap (mappedRegion, sbuf.st_size) != 0)
	{
		yield_error ("munmap() error");
		return;
	}

	// manipulated magic keyset should be detected now
	{
		// we expect an error here
		Key * parentKey = keyNew (TEST_ROOT_KEY, KEY_VALUE, tmpFile, KEY_END);
		KeySet * conf = ksNew (0, KS_END);
		PLUGIN_OPEN ("mmapstorage");

		KeySet * ks = ksNew (0, KS_END);
		succeed_if (plugin->kdbGet (plugin, ks, parentKey) == ELEKTRA_PLUGIN_STATUS_ERROR,
			    "kdbGet did not detect wrong magic keyset");

		keyDel (parentKey);
		ksDel (ks);
		PLUGIN_CLOSE ();
	}
}