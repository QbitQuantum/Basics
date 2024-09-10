	void indexSearch(size_t indexId, fstring key, valvec<llong>* recIdvec) override {
		assert(started == m_status);
		assert(indexId < m_indices.size());
		WT_ITEM item;
		WT_SESSION* ses = m_session.ses;
		const Schema& schema = m_sconf.getIndexSchema(indexId);
		WT_CURSOR* cur = m_indices[indexId].insert;
		WtWritableIndex::setKeyVal(schema, cur, key, 0, &item, &m_wrtBuf);
		recIdvec->erase_all();
		if (schema.m_isUnique) {
			int err = cur->search(cur);
			BOOST_SCOPE_EXIT(cur) { cur->reset(cur); } BOOST_SCOPE_EXIT_END;
			if (WT_NOTFOUND == err) {
				return;
			}
			if (err) {
				THROW_STD(invalid_argument
					, "ERROR: wiredtiger search: %s", ses->strerror(ses, err));
			}
			llong recId = 0;
			cur->get_value(cur, &recId);
			recIdvec->push_back(recId);
		}