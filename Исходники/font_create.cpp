int wuWriteFontDat( wJAf_t *wfont, char *filename, int pt_size )
{
	FILE *fp;
	char magic[4];
	magic[0] = 0;
	magic[1] = 0;
	magic[2] = 0;
	magic[3] = 0;
	float height, ascend, descend;
	int winning_baseline;
	int winning_height;
	int i;
	int def = 0;
	fp = fopen(filename, "wb");
	fseek( fp, 0, SEEK_SET );
	i = 0;
	while( i < 256 )
	{
/*void putf( float number, FILE *file );
void puts( int number, FILE *file );*/
		puts( wfont->glyph[i].phWidth, fp );
		puts( wfont->glyph[i].phHeight, fp );
		puts( wfont->glyph[i].hAdv, fp );
		puts( wfont->glyph[i].hOfs, fp );
		putw( wfont->glyph[i].baseline, fp );
		putf( wfont->glyph[i].st1[0], fp );
		putf( wfont->glyph[i].st1[1], fp );
		putf( wfont->glyph[i].st2[0], fp );
		putf( wfont->glyph[i].st2[1], fp );
		//printf( "char %1c (%d) %d %d %d %d %d | %2.2f %2.2f %2.2f %2.2f\n", i, i, wfont->glyph[i].phWidth, wfont->glyph[i].phHeight, wfont->glyph[i].hAdv, wfont->glyph[i].hOfs, wfont->glyph[i].baseline, wfont->glyph[i].st1[0], wfont->glyph[i].st1[1], wfont->glyph[i].st2[0], wfont->glyph[i].st2[1] );
		i++;
	}
	
	/*
	puts( wfont->mPointSize, fp );
	puts( wfont->mHeight, fp );
	puts( wfont->mAscender, fp );
	puts( wfont->mDescender, fp );
	*/
	/*
	puts( 16, fp );
	puts( 18, fp );
	puts( 16, fp );
	puts( 12, fp );
	*/
	float size_scale = (float)(pt_size) / (float)(wfont->mHeight);
	height = (float)(pt_size);
	//ascend = ((float)(wfont->mAscender) / (float)(wfont->mHeight)) * pt_size;
	//descend = ((float)(wfont->mDescender) / (float)(wfont->mHeight)) * pt_size;
	ascend = ((float)(wfont->mAscender) * size_scale);
	descend = ((float)(wfont->mDescender) * size_scale);
	descend -= size_scale * 12.0;
	int iascend, idescend;
	iascend = (int)(ascend);
	idescend = (int)(descend);
	//ascend = ((float)(wfont->mAscender)) * size_scale;
	//descend = ((float)(wfont->mDescender)) * size_scale;
	
	printf( "Font Junk: pt_size %d, height %d, Ascender %2.2f (%d), Descender %2.2f (%d)\n", pt_size, wfont->mHeight, ascend, iascend, descend, idescend );

	puts( iascend, fp );
	puts( pt_size, fp );
	puts( iascend, fp );
	puts( idescend, fp );
	//puts( 0, fp );
	//puts( 0, fp );
	puts( 0, fp );
	puts( 0, fp );
	fclose( fp );
}