NABoolean CmpSqlSession::validateVolatileName(const char * name)
{
  ComObjectName volTabName(name);

  NAString schemaNamePart = 
    volTabName.getSchemaNamePartAsAnsiString(TRUE);
  
  schemaNamePart.toUpper();

  ULng32 len = 
    MINOF(schemaNamePart.length(),
	  strlen(COM_VOLATILE_SCHEMA_PREFIX));

  if ((len < strlen(COM_VOLATILE_SCHEMA_PREFIX)) ||
      (strncmp(schemaNamePart.data(), COM_VOLATILE_SCHEMA_PREFIX, len) != 0))
    {
      return FALSE;
    }
  
  return TRUE;
}