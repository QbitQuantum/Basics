	/** Do the scan for GRFs. */
	static uint DoScan()
	{
		GRFFileScanner fs;
		return fs.Scan(".grf", DATA_DIR);
	}