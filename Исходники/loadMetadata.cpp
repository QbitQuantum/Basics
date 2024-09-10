void loadMetadata(Context & context)
{
	String path = context.getPath() + "metadata";

	/// Используется для параллельной загрузки таблиц.
	ThreadPool thread_pool(SettingMaxThreads().getAutoValue());

	/// Цикл по базам данных
	Poco::DirectoryIterator dir_end;
	for (Poco::DirectoryIterator it(path); it != dir_end; ++it)
	{
		if (!it->isDirectory())
			continue;

		/// Для директории .svn
		if (it.name().at(0) == '.')
			continue;

		String database = unescapeForFileName(it.name());

		/// Для базы данных может быть расположен .sql файл, где описан запрос на её создание.
		/// А если такого файла нет, то создаётся база данных с движком по-умолчанию.

		String database_attach_query;
		String database_metadata_file = it->path() + ".sql";

		if (Poco::File(database_metadata_file).exists())
		{
			ReadBufferFromFile in(database_metadata_file, 1024);
			readStringUntilEOF(database_attach_query, in);
		}
		else
			database_attach_query = "ATTACH DATABASE " + backQuoteIfNeed(database);

		executeCreateQuery(database_attach_query, context, database, it->path(), thread_pool);
	}

	thread_pool.wait();
}