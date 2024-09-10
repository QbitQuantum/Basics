MojErr MojDbKind::configureIndexes(const MojObject& obj, const MojString& locale, MojDbReq& req)
{
	MojLogTrace(s_log);

	// make sure indexes changes count against our usage
	MojErr err = req.curKind(this);
	MojErrCheck(err);

	// add default id index to set
	MojObject idIndex;
	err = idIndex.fromJson(IdIndexJson);
	MojErrCheck(err);
	ObjectSet newIndexObjects;
	err = newIndexObjects.put(idIndex);
	MojErrCheck(err);
	// change back to a set and use contains
	MojSet<MojString> indexNames;
	MojString defaultIdxName;
	err = defaultIdxName.assign(IdIndexName);
	MojErrCheck(err);
	err = indexNames.put(defaultIdxName);
	MojErrCheck(err);
	// add indexes to set to uniquify and order them
	MojObject indexArray;
	if (obj.get(IndexesKey, indexArray)) {
		MojObject::ConstArrayIterator end = indexArray.arrayEnd();
		for (MojObject::ConstArrayIterator i = indexArray.arrayBegin(); i != end; ++i) {
			MojString indexName;
			err = i->getRequired(MojDbIndex::NameKey, indexName);
			MojErrCheck(err);
			err = indexName.toLower();
			MojErrCheck(err);
			if (!indexNames.contains(indexName)) {
				MojObject idx = *i;
				// make sure we keep the lower-cased index name
				err = idx.putString(MojDbIndex::NameKey, indexName);
				MojErrCheck(err);
				err = newIndexObjects.put(idx);
				MojErrCheck(err);
				err = indexNames.put(indexName);
				MojErrCheck(err);
			} else {
				MojErrThrowMsg(MojErrDbInvalidIndexName, _T("db: cannot repeat index name: '%s'"), indexName.data());
			}
		}
	}
	// figure out what to add and what to delete
	ObjectSet toDrop;
	err = m_indexObjects.diff(newIndexObjects, toDrop);
	MojErrCheck(err);
	ObjectSet toAdd;
	err = newIndexObjects.diff(m_indexObjects, toAdd);
	MojErrCheck(err);
	// drop deleted indexes
	IndexVec newIndexes;
	for (IndexVec::ConstIterator i = m_indexes.begin(); i != m_indexes.end(); ++i) {
		if (toDrop.contains((*i)->object())) {
			err = dropIndex(i->get(), req);
			MojErrCheck(err);
		} else {
			err = newIndexes.push(*i);
			MojErrCheck(err);
		}
	}
	// add new indexes
	for (ObjectSet::ConstIterator i = toAdd.begin(); i != toAdd.end(); ++i) {
		// create index
		MojRefCountedPtr<MojDbIndex> index(new MojDbIndex(this, m_kindEngine));
		MojAllocCheck(index.get());
		err = index->fromObject(*i, locale);
		MojErrCheck(err);
		// open index
		err = openIndex(index.get(), req);
		MojErrCheck(err);
		err = newIndexes.push(index);
		MojErrCheck(err);
	}
	// sort indexes by the prop vec so that for indexes that share prop prefixes, the shortest one comes first
	err = newIndexes.sort();
	MojErrCheck(err);
	// update members
	m_indexObjects = newIndexObjects;
	m_indexes = newIndexes;

	return MojErrNone;
}