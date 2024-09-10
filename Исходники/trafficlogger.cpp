bool livestats::save(FILE *fd, reltimes & times) {
	// these are the time periods we store data for
	std::vector<std::string> range = times.all_range();
	std::map<std::string,int> ::iterator h; 
	std::map<std::string,bytecount_t> ::iterator i;  
	std::set<std::string> ::iterator devidx,ruleidx, addridx;
	// classes need to be kept in specific - non sorted order
	std::vector<std::string> ::iterator classidx;
	std::set<std::string> ::iterator j;
	std::map<std::string, int> &nc_current_rates = const_cast<std::map<std::string, int> &>(current_rates); 

	// only do stuff if we have some fresh data to save yet
	if(nc_current_rates.size() == 0)
		return false;
	// lock this file
	rewind(fd);
	lockf(fileno(fd), F_LOCK, 0);
	// timestamp first
	fprintf(fd,"last_update=%ld\n", last_update.t.tv_sec);
	// then whole interface stats, only now save for devs that are present - this is a bug, needs to be fixed
	if(ext_devs.size() > 0) {
		for(j = ext_devs.begin(); j != ext_devs.end(); j++) {
			save_rate_helper(fd, "cur_inc_rate_" + *j);                
			save_rate_helper(fd, "cur_out_rate_" + *j);
		
			// and for each time period, totals are scaled down to kbytes
			save_period_helper(fd, "_inc_total_" + *j, range);
			save_period_helper(fd, "_out_total_" + *j, range);
		
			// then class stats
			for (classidx = classes.begin(); classidx != classes.end(); classidx++) {
				save_rate_helper(fd, "cur_out_rate_" + *j + "_class_" + *classidx);
				save_period_helper(fd, "_out_total_" + *j + "_class_" + *classidx, range);
				save_rate_helper(fd, "cur_inc_rate_" + *j + "_class_" + *classidx);
				save_period_helper(fd, "_inc_total_" + *j + "_class_" + *classidx, range);
			}
		  
			// then rule stats
			for (ruleidx = rules.begin(); ruleidx != rules.end(); ruleidx++) { 
				save_rate_helper(fd, "cur_out_rate_" + *j + "_rule_" + *ruleidx);
				save_period_helper(fd, "_out_total_" + *j + "_rule_" + *ruleidx, range);
				save_rate_helper(fd, "cur_inc_rate_" + *j + "_rule_" + *ruleidx);
				save_period_helper(fd, "_inc_total_" + *j + "_rule_" + *ruleidx, range);
			}
		} // dev loop
	} // ext devs
	if(int_devs.size() > 0) {
		for(j = int_devs.begin(); j != int_devs.end(); j++) {
			save_rate_helper(fd, "cur_inc_rate_" + *j);                
			save_rate_helper(fd, "cur_out_rate_" + *j);
			// and for each time period, totals are scaled down to kbytes
			save_period_helper(fd, "_inc_total_" + *j, range);
			save_period_helper(fd, "_out_total_" + *j, range);
			// then class stats
			for (classidx = classes.begin(); classidx != classes.end(); classidx++) {
				save_rate_helper(fd, "cur_out_rate_" + *j + "_class_" + *classidx);
				save_period_helper(fd, "_out_total_" + *j + "_class_" + *classidx, range); 
				save_rate_helper(fd, "cur_inc_rate_" + *j + "_class_" + *classidx);
				save_period_helper(fd, "_inc_total_" + *j + "_class_" + *classidx, range);
			}
			// then rule stats
			for (ruleidx = rules.begin(); ruleidx != rules.end(); ruleidx++) { 
				save_rate_helper(fd, "cur_out_rate_" + *j + "_rule_" + *ruleidx);
				save_period_helper(fd, "_out_total_" + *j + "_rule_" + *ruleidx, range); 
				save_rate_helper(fd, "cur_inc_rate_" + *j + "_rule_" + *ruleidx);
				save_period_helper(fd, "_inc_total_" + *j + "_rule_" + *ruleidx, range);
			}
		}
	}
	for(addridx = addresses.begin(); addridx != addresses.end(); addridx++) {
		const std::string & address = *addridx;
		std::string direction = "(dn)";
		std::string addr = "0.0.0.0";
		std::string::size_type pos = address.find("(");
		if(pos != std::string::npos) {
			direction = address.substr(pos);
			addr = address.substr(0,pos);
		}
		if(direction == "(dn)") {
			save_rate_helper(fd, "cur_inc_rate_" + addr);
			save_period_helper(fd, "_inc_total_" + addr, range);
		}
		else {
			save_rate_helper(fd, "cur_out_rate_" + addr);
			save_period_helper(fd, "_out_total_" + addr, range);
		}
	}
	
	// truncate the file at this point
	ftruncate(fileno(fd), ftell(fd)); 
	fflush(fd);
	// now unlock
	rewind(fd);
	lockf(fileno(fd), F_ULOCK, 0);
	
	return true;

}