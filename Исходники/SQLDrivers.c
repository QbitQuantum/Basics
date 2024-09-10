SQLRETURN SQL_API
SQLDriversA(SQLHENV EnvironmentHandle,
	    SQLUSMALLINT Direction,
	    SQLCHAR *DriverDescription,
	    SQLSMALLINT BufferLength1,
	    SQLSMALLINT *DescriptionLengthPtr,
	    SQLCHAR *DriverAttributes,
	    SQLSMALLINT BufferLength2,
	    SQLSMALLINT *AttributesLengthPtr)
{
	return SQLDrivers(EnvironmentHandle,
			  Direction,
			  DriverDescription,
			  BufferLength1,
			  DescriptionLengthPtr,
			  DriverAttributes,
			  BufferLength2,
			  AttributesLengthPtr);
}