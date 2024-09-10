BlockInputStreamPtr MongoDBDictionarySource::loadAll()
{
	return std::make_shared<MongoDBBlockInputStream>(
		connection, createCursor(db, collection, sample_block), sample_block, max_block_size);
}