SQLRETURN SQL_API
SQLGetConnectAttrA(SQLHDBC ConnectionHandle,
		   SQLINTEGER Attribute,
		   SQLPOINTER ValuePtr,
		   SQLINTEGER BufferLength,
		   SQLINTEGER *StringLengthPtr)
{
	return SQLGetConnectAttr(ConnectionHandle,
				 Attribute,
				 ValuePtr,
				 BufferLength,
				 StringLengthPtr);
}