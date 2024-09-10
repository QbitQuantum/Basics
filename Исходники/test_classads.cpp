/*********************************************************************
 *
 * Function: process_truncate_log
 * Purpose:  
 *
 *********************************************************************/
static void process_truncate_log(
	const string &line,
	int token_start, int line_number, 
	const Parameters &parameters,
	ErrorCount *errors)
{
	string collection_name;

	collection_name = extract_token(&token_start, line);
	if (!collection_name.compare("") || !collection_name.compare("")) {
		cout << "Error: Missing add-to-collection information on line " << line_number 
			 << "." << endl;
		cout << "       Format: add-to-collection <collection-name> <classad-name>" << endl;
		errors->IncrementErrors();
	}
	else {
		ClassAdCollection *collection;

		collection = collections[collection_name];
		if (collection == NULL ) {
			cout << "Error: Unknown collection (" << collection_name 
				 << ") on line " << line_number  << "." << endl;
			errors->IncrementErrors();
		}
		else {
			bool success;
			success = collection->TruncateLog();
			if (!success) {
				cout << "Error: couldn't truncate log for " << collection_name 
					 << " on line " << line_number << ".\n";
				cout << "  (Error is: " << CondorErrMsg << ")\n";
				errors->IncrementErrors();
			} else {
				cout << "OK: Truncated log for " << collection_name
					 << " on line " << line_number << ".\n";
			}
		}
	}

	return;
}