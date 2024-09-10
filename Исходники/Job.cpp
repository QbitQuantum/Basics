//---------------------------------------------------------------------------
const char *
Job::GetJobstateJobTag()
{
	if ( !_jobTag ) {
		MyString jobTagName = MultiLogFiles::loadValueFromSubFile(
					_cmdFile, _directory, JOB_TAG_NAME );
		if ( jobTagName == "" ) {
			jobTagName = PEGASUS_SITE;
		} else {
				// Remove double-quotes
			int begin = jobTagName[0] == '\"' ? 1 : 0;
			int last = jobTagName.Length() - 1;
			int end = jobTagName[last] == '\"' ? last - 1 : last;
			jobTagName = jobTagName.Substr( begin, end );
		}

		MyString tmpJobTag = MultiLogFiles::loadValueFromSubFile(
					_cmdFile, _directory, jobTagName.Value() );
		if ( tmpJobTag == "" ) {
			tmpJobTag = "-";
		} else {
				// Remove double-quotes
			int begin = tmpJobTag[0] == '\"' ? 1 : 0;
			int last = tmpJobTag.Length() - 1;
			int end = tmpJobTag[last] == '\"' ? last - 1 : last;
			tmpJobTag = tmpJobTag.Substr( begin, end );
		}
		_jobTag = strnewp( tmpJobTag.Value() );
	}

	return _jobTag;
}