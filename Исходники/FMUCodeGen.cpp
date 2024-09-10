std::string FMUCodeGen::generateGUID()
{
	UUID uuid;     
	UuidCreate ( &uuid );      
	unsigned char * str;     
	UuidToStringA ( &uuid, &str );      
	std::string guid( ( char* ) str );
	guid = "{"+guid+"}";
	RpcStringFreeA ( &str ); 
	return guid;
}