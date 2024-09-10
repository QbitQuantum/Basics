void CCSVWriter::WriteRevProps (std::ostream& os, const CCachedLogInfo& cache)
{
	// header

	os << "ID,Revision,RevPropID,Value\n";

	// content

	const CRevisionIndex& revisions = cache.GetRevisions();
	const CRevisionInfoContainer& logInfo = cache.GetLogInfo();

	// ids will be added on-the-fly

	size_t id = 0;
	for ( revision_t revision = revisions.GetFirstRevision()
		, last = revisions.GetLastRevision()
		; revision < last
		; ++revision)
	{
		index_t index = revisions[revision];
        if (index == NO_INDEX)
            continue;

		typedef CRevisionInfoContainer::CUserRevPropsIterator RI;

		if (  logInfo.GetPresenceFlags (index) 
            & CRevisionInfoContainer::HAS_USERREVPROPS)
		{
			// we actually have a valid (possibly empty) merge list 
			// for this revision

			for ( RI iter = logInfo.GetUserRevPropsBegin (index)
				, end = logInfo.GetUserRevPropsEnd (index)
				; iter != end
				; ++iter)
			{
				std::string value = iter->GetValue();
				Escape (value);

				os << id++ << ',' 
				   << revision << ','
				   << iter->GetNameID()<< ",\""
				   << value.c_str()
				   << "\"\n";
			}
		}
	}
}