bool updateProcessStats( ProcessInfo &pi )
{
	char pinfoFilename[64];
	FvSNPrintf( pinfoFilename, sizeof( pinfoFilename ),
		"/proc/%d/stat", (int)pi.m.pid_ );

	FILE *pinfo;
	if ((pinfo = fopen( pinfoFilename, "r" )) == NULL)
	{
		if (errno != ENOENT)
		{
			syslog( LOG_ERR, "Couldn't open %s: %s",
				pinfoFilename, strerror( errno ) );
		}

		return false;
	}

	int utime, stime, vsize, cpu;
	getProcessTimes( pinfo, &utime, &stime, &vsize, &cpu );
	pi.cpu.update( utime + stime );
	pi.mem.update( vsize );
	pi.affinity = cpu;

	fclose( pinfo );
	return true;
}