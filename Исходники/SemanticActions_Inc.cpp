	void operator()(const char *begin, const char *end) const
 	{
 		std::string text = std::string(begin, end);
 		CString ctext = text.c_str();
#ifdef DEBUG_USER_VARIABLES
		cout << endl << "Uservariable to be set: " << ctext << endl;	
#endif 
		// Removing underscores, as they are used as separators
		// and would mix things up, e.g. me_st_Pi_3_141592653
		ctext.Remove('_');
 		//Add to list of user variables if not yet known
 		CSMap::const_iterator find_result = user_vars.find(ctext.MakeLower());
 		if (find_result == user_vars.end())
 		{
 			user_vars[ctext.MakeLower()] = ctext.MakeLower();
 		}
 		when_conditions_since_last_action = 0;
 		if (open_ended_when_condition_detected)
 		{
 			cout << current_open_ended_when_condition.str() << "  &&  ["
 				 << current_when_condition.str() << " ? "
 				 << "me_st_" << ctext.MakeLower() << "_1 : 0] && 0 ? 0 :" << endl;
 		}
 		else
 		{
 			cout << "[ " << current_when_condition.str() << " ? "
 				 << "me_st_" << ctext.MakeLower() << "_1 : 0] && 0 ? 0 :" << endl;
 		}
 		current_output.str("");
 		current_output.clear();
 	}