bool ContextBase::isValidState()
{
	if (!openFiles()) {
		return false;
	}
	if (!cmdArgsValid()) {
		return false;
	}
	if (!determineOutputType()) {
		return false;
	}
	if (hasColumnOpsMethods()) {
		FileRecordMgr *dbFile = getFile(hasIntersectMethods() ? _databaseFileIdx : 0);
		_keyListOps->setDBfileType(dbFile->getFileType());
		if (!_keyListOps->isValidColumnOps(dbFile)) {
			return false;
		}
	}
	return true;
}