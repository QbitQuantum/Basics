// 底层日志函数实现
void _file_logger( FILE *fp, va_list ap, const char *format ) {
	if ( fp == NULL ) return;
	
	// prefix datetime
	DateTime now;
	String logformat;
	logformat.sprintf( "%s\t%s", now.datetime().c_str(), format );

	// log content
	vfprintf( fp, logformat.c_str(), ap );
	fputc( '\n', fp );
}