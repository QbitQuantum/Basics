void VFSHandle_file::WriteString( char *s, unsigned int length )
{
	WriteRaw( ( unsigned char * ) s, length );
}