SQLRETURN SQL_API
SQLColAttributesA(SQLHSTMT StatementHandle,
		  SQLUSMALLINT ColumnNumber,
		  SQLUSMALLINT FieldIdentifier,
		  SQLPOINTER CharacterAttributePtr,
		  SQLSMALLINT BufferLength,
		  SQLSMALLINT *StringLengthPtr,
		  SQLLEN *NumericAttributePtr)
{
	return SQLColAttributes(StatementHandle,
				ColumnNumber,
				FieldIdentifier,
				CharacterAttributePtr,
				BufferLength,
				StringLengthPtr,
				NumericAttributePtr);
}