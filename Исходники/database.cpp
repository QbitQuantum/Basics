Database::Database()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_rc = sqlite3_open("c://database.db", &_db);
#else
	string path=CCFileUtils::getInstance()->getWritablePath() + "begins.db";
	_rc = sqlite3_open(path.c_str(), &_db);
#endif

	CreateTable();

	_initialized = true;
	_queryP.self = this;
}