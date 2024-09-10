void searchPath(const CmdLineOptions &myOptions, boost::shared_ptr<BoundedQueue<std::string>> fileQueue, boost::exception_ptr & error)
{
  if (myOptions.debug > 1)
    std::cout << "Started search of path: " << myOptions.root_search_path << std::endl;
  
  fs::path p,sym_path,abs_path, temp_path;
  fs::recursive_directory_iterator end, it(myOptions.root_search_path);
  try {
    // use absolute paths for comparisons
    abs_path = fs::canonical(myOptions.root_search_path);
    do {     // Can't use for loop because we need a try block. See below
      try {
	p = it->path();
        if (fs::is_symlink(p)) {
	  temp_path = fs::canonical(p);
	  if (fs::is_directory(temp_path)) {
	    if (abs_path <= temp_path) {
	      if (myOptions.debug > 2) {
		std::cout << "Skipping " << p.string()
			  << " because it is a symlink to the path: " << temp_path.string() << std::endl;
	      }
	      // since its a directory, can skip file handling code below
	      it.no_push();
	    }
	    // continue recursing directory
	  }
	  else { // this is a file
	    if (p.extension().string() == ".txt") { // more efficient to filter on extension than lexigraphical compare
	      if (abs_path <= temp_path.remove_filename()) { // modifies sym_path
		if (myOptions.debug > 2) {
		  std::cout << "Skipping " << p.string()
			    << " because it is a symlink to the path: " << fs::canonical(p).string() << std::endl;
		}
		// skip this file
		it.no_push();
	      }
	    }
	    /* The symlink is to a regular file, so just fall through */
	  }
	}
	else if (fs::is_regular_file(p)) {
	  if (p.extension().string() == ".txt") {
	    if (myOptions.debug > 1) {
	      std::cout << "searchWorker: " << p.string() << " placed on queue\n";
	    }
	    // we want to place a copy of the string on the queue, but the queue is written in a way to 
	    // accept rvalue arguments
	    std::string _file = p.string();
	    fileQueue->send(std::move(_file));
	  }
	}
	try{  // boost bug 6821: recursive_directory_iterator: increment fails with 'access denied'
	  ++it;
	}
	catch(const boost::filesystem::filesystem_error& e) {
	  if(e.code() == boost::system::errc::permission_denied) {
	    std::cerr << "Search permission is denied for:  " << p.string() << "\n";
	  }
	  it.no_push();
	}
      }
      catch(const boost::filesystem::filesystem_error& e) {
	if(e.code() == boost::system::errc::permission_denied) {
	  std::cerr << "Search permission is denied for:  " << p.string() << "\n";
	}
	else if(e.code() == boost::system::errc::no_such_file_or_directory) {
	  std::cerr << "Symlink " << p.string() << " points to non-existent file\n";
	}
	else if(e.code() == boost::system::errc::too_many_symbolic_link_levels) {
	  std::cerr << "Encountered too many symbolic link levels at: " << p.string() << " . Not continuing\n";
	  // boost bug 5652 -- fixed in 1.49.0
	}
	else {
	  /* Not sure how to hande other errors, so continue propogating */
	  std::cerr << "Fatal error detected in directory search: " << e.what() << std::endl;
	  // shut down threads
	  fileQueue->send("");
	  throw boost::enable_current_exception(recursive_directory_iterator_error()) <<
	    boost::errinfo_errno(errno);
	}
	it.no_push();
	++it;
      }
    } while (it != end);

    // finished with indexing root path now
    // place termination character on queue
    fileQueue->send("");
    
    // all errors were handled, so don't pass any outside this thread
    error = boost::exception_ptr();
  }
  catch (const boost::exception& e) {
    std::cout << "searchWorker encountered unexpected exception" << diagnostic_information(e) << std::endl;
    error = boost::current_exception();
  }
  catch (...) {
    error = boost::current_exception();
  }

  if (myOptions.debug > 1)
    std::cout << "Finished search of path: " << myOptions.root_search_path << std::endl;
}