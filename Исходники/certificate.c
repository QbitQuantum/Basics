void certificate_store_init(rdpCertificateStore* certificate_store)
{
	rdpSettings* settings;

	settings = certificate_store->settings;

	if (!PathFileExistsA(settings->ConfigPath))
	{
		CreateDirectoryA(settings->ConfigPath, 0);
		fprintf(stderr, "creating directory %s\n", settings->ConfigPath);
	}

	certificate_store->path = GetCombinedPath(settings->ConfigPath, (char*) certificate_store_dir);

	if (!PathFileExistsA(certificate_store->path))
	{
		CreateDirectoryA(certificate_store->path, 0);
		fprintf(stderr, "creating directory %s\n", certificate_store->path);
	}

	certificate_store->file = GetCombinedPath(settings->ConfigPath, (char*) certificate_known_hosts_file);

	if (PathFileExistsA(certificate_store->file) == FALSE)
	{
		certificate_store->fp = fopen((char*) certificate_store->file, "w+");

		if (certificate_store->fp == NULL)
		{
			fprintf(stderr, "certificate_store_open: error opening [%s] for writing\n", certificate_store->file);
			return;
		}

		fflush(certificate_store->fp);
	}
	else
	{
		certificate_store->fp = fopen((char*) certificate_store->file, "r+");
	}
}