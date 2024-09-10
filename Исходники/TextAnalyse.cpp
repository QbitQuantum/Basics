//指定のテキストファイルがユニコードかどうかを判定する(true:ユニコード  false:マルチバイト)
bool TextAnalyseW::checkUnicode( const char *path )
{
	FILEPOINTER fp;
	unsigned char temp[2];

	fp = FOPEN( path );
	if( fp == 0 ) return false;
	FREAD( temp, 2, fp );
	FCLOSE( fp );

	return temp[0] == 0xff && temp[1] == 0xfe;
}