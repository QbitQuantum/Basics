int SQLiteResult::fieldNum(const String &fieldname)
{
	if (!stmt) throw NoResultException();
	if (fieldname.isEmpty()) throw IllegalArgumentException();
	if (last_res!=SQLITE_ROW) throw NoResultException();
	for (int i=0;i<num_fields;i++) {
		if (fieldname.strcmp(sqlite3_column_name(stmt,i))==0) {
			return i;
		}
	}
	throw FieldNotInResultSetException(fieldname);
}