int main(int argc, char* argv[])
{
	// Program parameters
	unsigned long bit_size = DEFAULT_BITSIZE;
	unsigned long num_attribs = 0;
	unsigned long counter = 0;
	time_t expiry = std::time(NULL);
	std::string pub_key_filename;
	std::string priv_key_filename;
	std::string base_URI = DEFAULT_BASE_URI;
	int c = 0;
	
	// Add a year to expiry and round it down to 1 day
	struct tm* now = localtime(&expiry);
	now->tm_year = now->tm_year + 1;
	now->tm_hour = 0;
	now->tm_min = 0;
	now->tm_sec = 0;
	expiry = mktime(now);

	while ((c = getopt(argc, argv, "a:n:c:d:p:P:u:hv")) != -1)
	{
		switch (c)
		{
		case 'h':
			usage();
			return 0;
		case 'v':
			version();
			return 0;
		case 'a':
			num_attribs = strtoul(optarg, NULL, 10);
			break;
		case 'n':
			bit_size = strtoul(optarg, NULL, 10);
			break;
		case 'c':
			counter = strtoul(optarg, NULL, 10);
			break;
		case 'd':
			expiry = strtoul(optarg, NULL, 10);
			break;
		case 'p':
			pub_key_filename = std::string(optarg);
			break;
		case 'P':
			priv_key_filename = std::string(optarg);
			break;
		case 'u':
			base_URI = std::string(optarg);
			break;
		}
	}
	
	if (num_attribs <= 0)
	{
		fprintf(stderr, "Missing argument -a; please specify a number of attributes\n");
		
		return -1;
	}
	
	FILE* pub_key_file = stdout;
	FILE* priv_key_file = stdout;
	
	if (!pub_key_filename.empty())
	{
		pub_key_file = fopen(pub_key_filename.c_str(), "w");
		
		if (pub_key_file == NULL)
		{
			fprintf(stderr, "Failed to open %s for writing\n", pub_key_filename.c_str());
			
			return -1;
		}
		
		printf("Writing public key to %s\n", pub_key_filename.c_str());
	}
	
	if (!priv_key_filename.empty())
	{
		priv_key_file = fopen(priv_key_filename.c_str(), "w");
		
		if (priv_key_file == NULL)
		{
			fprintf(stderr, "Failed to open %s for writing\n", priv_key_filename.c_str());
			
			return -1;
		}
		
		printf("Writing private key to %s\n", priv_key_filename.c_str());
	}
	
	generate_key_pair(pub_key_file, priv_key_file, base_URI, num_attribs, bit_size, counter, expiry);
	
	if (!pub_key_filename.empty()) fclose(pub_key_file);
	if (!priv_key_filename.empty()) fclose(priv_key_file);
	
	return 0;
}