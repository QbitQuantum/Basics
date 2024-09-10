/**
 * 故障恢复时REDO创建表操作
 *
 * @param db 数据库对象
 * @param session 会话
 * @param path 小型大对象文件路径
 * @param tableId 虚拟表ID
 * @throw NtseException 文件操作出错等
 */
void SmallLobStorage::redoCreate(Database *db, Session *session, const char *basePath, u16 tableId) throw(NtseException) {
	string heapPath = string(basePath) + Limits::NAME_SOBH_EXT;
	string tblDefPath = string(basePath) + Limits::NAME_SOBH_TBLDEF_EXT;
	u16 vTableId = TableDef::getVirtualLobTableId(tableId);;
	TableDef *vtableDef = createTableDef(vTableId, VIRTUAL_TABLE_NAME);
	vtableDef->m_cacheUpdate = false;
	bool createVTbl = false;
	try {
		vtableDef->writeFile(tblDefPath.c_str());
		createVTbl = true;
		DrsHeap::redoCreate(db, session, heapPath.c_str(), vtableDef);
	} catch (NtseException &e) {
		if (createVTbl) {
			TableDef::drop(tblDefPath.c_str());
		}
		delete vtableDef;
		throw e;
	}
	delete vtableDef;
}