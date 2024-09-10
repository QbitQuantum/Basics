SQLRETURN SQL_API
SQLColAttributeA(SQLHSTMT StatementHandle,
		 SQLSMALLINT ColumnNumber,
		 SQLSMALLINT FieldIdentifier,
		 SQLPOINTER CharacterAttributePtr,
		 SQLSMALLINT BufferLength,
		 SQLSMALLINT *StringLengthPtr,
		 LENP_OR_POINTER_T NumericAttributePtr)
{
	return SQLColAttribute(StatementHandle,
			       (SQLUSMALLINT) ColumnNumber,
			       (SQLUSMALLINT) FieldIdentifier,
			       CharacterAttributePtr,
			       BufferLength,
			       StringLengthPtr,
			       NumericAttributePtr);
}