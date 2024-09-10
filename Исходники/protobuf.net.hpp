void 
RequestHandler::update_duties (void) {
	boost::mutex::scoped_lock lock(m);
	RequestHandler* obj;
	BOOST_FOREACH(obj, off_duties) {
		// vector<RequestHandler*>::iterator end_it = on_duties.remove (on_duties.begin(), on_duties.end(), obj);
		// on_duties.erase (end_it, on_duties.end());
		on_duties.remove (obj);
		delete obj;
	}