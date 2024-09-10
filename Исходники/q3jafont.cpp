void ReadJAFont( char *filename, jafont_t font[256], jahead_t head )
{
	FILE *fp;
	fp = fopen(filename, "rb");
	int i;
	i = 32;
	fseek( fp, 896, SEEK_SET );
	while( i < 255 )
	{
		font[i].phWidth = gets( fp );
		font[i].phHeight = gets( fp );
		font[i].hAdv = gets( fp );
		font[i].hOfs = gets( fp );
		font[i].baseline = getw( fp );
		font[i].st1[0] = getf( fp );
		font[i].st1[1] = getf( fp );
		font[i].st2[0] = getf( fp );
		font[i].st2[1] = getf( fp );
		i++;
	}
	head.mPointSize = gets( fp );
	head.mHeight = gets( fp );
	head.mAscender = gets( fp );
	head.mDescender = gets( fp );
	head.mKoreanHack = gets( fp );
	fclose( fp );
}