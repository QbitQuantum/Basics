void HashTableDb::set(const std::string& key, const std::string& value)
{
	size_t hashCode = getHash(key) & hashMask;
	try
	{
		DbRecord rec = ht->get(hashCode, key.c_str()).getRecord(*db);
		if (rec.canShrink(key.c_str(), value.c_str()))
		{
			db->shrinkRecord(rec, key.c_str(), value.c_str());
		}
		else
		{
			db->delRecord(rec);
			ht->del(hashCode, key.c_str());

			DbRecord newRec = db->newRecord(key.c_str(), value.c_str());
			ht->add(hashCode, key.c_str(), newRec.getPage()->getId(), newRec.getCursor());
		}
	}
	catch (IndexFile::IndexNotFound)
	{
		DbRecord newRec = db->newRecord(key.c_str(), value.c_str());
		ht->add(hashCode, key.c_str(), newRec.getPage()->getId(), newRec.getCursor());
	}
}