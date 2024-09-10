//-------------------------------------------------------------------------
bool
GetConfigAndAttrs( /* const */ StringList &dagFiles, bool useDagDir, 
			MyString &configFile, StringList &attrLines, MyString &errMsg )
{
	bool		result = true;

		// Note: destructor will change back to original directory.
	TmpDir		dagDir;

	dagFiles.rewind();
	char *dagFile;
	while ( (dagFile = dagFiles.next()) != NULL ) {

			//
			// Change to the DAG file's directory if necessary, and
			// get the filename we need to use for it from that directory.
			//
		const char *	newDagFile;
		if ( useDagDir ) {
			MyString	tmpErrMsg;
			if ( !dagDir.Cd2TmpDirFile( dagFile, tmpErrMsg ) ) {
				AppendError( errMsg,
						MyString("Unable to change to DAG directory ") +
						tmpErrMsg );
				return false;
			}
			newDagFile = condor_basename( dagFile );
		} else {
			newDagFile = dagFile;
		}

		StringList		configFiles;

			// Note: destructor will close file.
		MultiLogFiles::FileReader reader;
		errMsg = reader.Open( newDagFile );
		if ( errMsg != "" ) {
			return false;
		}

		MyString logicalLine;
		while ( reader.NextLogicalLine( logicalLine ) ) {
			if ( logicalLine != "" ) {
					// Note: StringList constructor removes leading
					// whitespace from lines.
				StringList tokens( logicalLine.Value(), " \t" );
				tokens.rewind();

				const char *firstToken = tokens.next();
				if ( !strcasecmp( firstToken, "config" ) ) {

						// Get the value.
					const char *newValue = tokens.next();
					if ( !newValue || !strcmp( newValue, "" ) ) {
						AppendError( errMsg, "Improperly-formatted "
									"file: value missing after keyword "
									"CONFIG" );
			    		result = false;
					} else {

							// Add the value we just found to the config
							// files list (if it's not already in the
							// list -- we don't want duplicates).
						configFiles.rewind();
						char *existingValue;
						bool alreadyInList = false;
						while ( ( existingValue = configFiles.next() ) ) {
							if ( !strcmp( existingValue, newValue ) ) {
								alreadyInList = true;
							}
						}

						if ( !alreadyInList ) {
								// Note: append copies the string here.
							configFiles.append( newValue );
						}
					}

					//some DAG commands are needed for condor_submit_dag, too...
				} else if ( !strcasecmp( firstToken, "SET_JOB_ATTR" ) ) {
						// Strip of DAGMan-specific command name; the
						// rest we pass to the submit file.
					logicalLine.replaceString( "SET_JOB_ATTR", "" );
					logicalLine.trim();
					if ( logicalLine == "" ) {
						AppendError( errMsg, "Improperly-formatted "
									"file: value missing after keyword "
									"SET_JOB_ATTR" );
						result = false;
					} else {
						attrLines.append( logicalLine.Value() );
					}
				}
			}
		}
	
		reader.Close();

			//
			// Check the specified config file(s) against whatever we
			// currently have, setting the config file if it hasn't
			// been set yet, flagging an error if config files conflict.
			//
		configFiles.rewind();
		char *		cfgFile;
		while ( (cfgFile = configFiles.next()) ) {
			MyString	cfgFileMS = cfgFile;
			MyString	tmpErrMsg;
			if ( MakePathAbsolute( cfgFileMS, tmpErrMsg ) ) {
				if ( configFile == "" ) {
					configFile = cfgFileMS;
				} else if ( configFile != cfgFileMS ) {
					AppendError( errMsg, MyString("Conflicting DAGMan ") +
								"config files specified: " + configFile +
								" and " + cfgFileMS );
					result = false;
				}
			} else {
				AppendError( errMsg, tmpErrMsg );
				result = false;
			}
		}

			//
			// Go back to our original directory.
			//
		MyString	tmpErrMsg;
		if ( !dagDir.Cd2MainDir( tmpErrMsg ) ) {
			AppendError( errMsg,
					MyString("Unable to change to original directory ") +
					tmpErrMsg );
			result = false;
		}
	}

	return result;
}