int ReadTextureFromFile( struct Texture * t, const char * filename )
{
	int i;
	HGLOBAL hMem;
	LPVOID pMemImage;
	IStream *pStm;
	struct GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GpBitmap *pImg;
	PixelFormat PixelFormat;

	//Read in data
	FILE * f = fopen( filename, "rb");
	if( !f )
	{
		fprintf( stderr, "Error: Could not open %s\n", filename );
		return -1;
	}
	fseek(f,0,SEEK_END);
	int l = ftell( f );
	unsigned char * buffer = malloc( l );
	fseek(f,0,SEEK_SET);
	fread(buffer, l, 1, f );
	fclose( f );

	//Prepare GDI+ imaging
	hMem = GlobalAlloc( GMEM_MOVEABLE, l );
	pMemImage = GlobalLock( hMem);
	memcpy( pMemImage, buffer, l );
	GlobalUnlock( hMem );

	//XXX: This requries OLE32, do we really want it?
	CreateStreamOnHGlobal( hMem, TRUE, &pStm );

	gdiplusStartupInput.GdiplusVersion = 1;
	gdiplusStartupInput.DebugEventCallback = NULL;
	gdiplusStartupInput.SuppressBackgroundThread = FALSE;
	gdiplusStartupInput.SuppressExternalCodecs = FALSE;
	GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL );

	if( GdipCreateBitmapFromStream( pStm, &pImg ) )
	{
		fprintf( stderr, "Error: cannot decode: %s\n", filename );
		return -2;
	}

	GdipGetImagePixelFormat( (GpImage *)pImg, &PixelFormat );

	UINT width;
	UINT height;
	GdipGetImageHeight( (GpImage *)pImg, &height );
	GdipGetImageWidth( (GpImage *)pImg, &width );
	GpRect r;
	r.X = 0;
	r.Y = 0;
	r.Width = width;
	r.Height = height;
	BitmapData bd;

		enum TextureType format;
	GLenum type; //Almost always GL_TEXTURE_2D (Could be GL_TEXTURE_3D)
	GLuint texture;

	int slot; //which texture slot (For multi-texturing)
	uint8_t * rawdata; //May be other types, too!

	t->width = width;
	t->height = height;
	t->type = GL_TEXTURE_2D;

	//Detect if has alpha or not...
	int ps;
	if( PixelFormat & PixelFormatAlpha )
	{
		GdipBitmapLockBits(pImg,&r,ImageLockModeRead,PixelFormat32bppARGB,&bd);
		ps = 4;
		t->format = TTRGBA;
	}
	else
	{
		GdipBitmapLockBits(pImg,&r,ImageLockModeRead,PixelFormat24bppRGB,&bd);
		ps = 3;
		t->format = TTRGB;
	}

	t->rawdata = malloc( ps * width * height );

	int x, y;
	if( ps == 3 )
	{
		for( y = 0; y < height; y++ )
		for( x = 0; x < width; x++ )
		{
			t->rawdata[(x+y*width)*3+0] = ((unsigned char*)bd.Scan0)[x*3+y*bd.Stride+2];
			t->rawdata[(x+y*width)*3+1] = ((unsigned char*)bd.Scan0)[x*3+y*bd.Stride+1];
			t->rawdata[(x+y*width)*3+2] = ((unsigned char*)bd.Scan0)[x*3+y*bd.Stride+0];
		}
	}
	else //ps = 4
	{
		for( y = 0; y < height; y++ )
		for( x = 0; x < width; x++ )
		{
			t->rawdata[(x+y*width)*4+0] = ((unsigned char*)bd.Scan0)[x*4+y*bd.Stride+2];
			t->rawdata[(x+y*width)*4+1] = ((unsigned char*)bd.Scan0)[x*4+y*bd.Stride+1];
			t->rawdata[(x+y*width)*4+2] = ((unsigned char*)bd.Scan0)[x*4+y*bd.Stride+0];
			t->rawdata[(x+y*width)*4+3] = ((unsigned char*)bd.Scan0)[x*4+y*bd.Stride+3];
		}
	}

	GdipBitmapUnlockBits(pImg, &bd );
	GdipDisposeImage( (GpImage *)pImg );
	GdiplusShutdown( gdiplusToken );

	return 0;
}