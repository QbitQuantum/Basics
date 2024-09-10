bool PfffFindDuplicatesOptionManager::validate() {
    if (help) return true;
    try {
    	if (parameters.size() == 0)
    		throw (char*)"Error: No files to process.";
    	if (!key_given) {
            srand ( time(NULL) );
            key = rand();
        }
        if (http_given && ftp_given)
            throw (char*)"Error: Both HTTP and FTP may not be requested.";
        
        // Set default port
        if (!port_given) {
            if (http_given) port = 80;
            else if (ftp_given) port = 21;
        }
    	
    	// If we're using ftp and haven't specified request_cost, set a 
    	// reasonable default.
    	if (!request_cost_given && ftp_given) request_cost = 1024000; 
    	
    	// Now fill in the options structure
        pfff_options_init(&options, key);
        options.block_count = block_count;
        options.block_size = block_size;
        options.header_block_count = header_block_count;
        options.without_replacement = without_replacement;
        options.with_size = with_size;
        options.no_prefix = true;
        options.no_filename = true;
        
        char* errmsg;
        if (pfff_options_validate(&options, &errmsg)) return true;
        else throw errmsg;
    }
    catch(char* msg) {
        error_message = string(msg);
        return false;
    }
}