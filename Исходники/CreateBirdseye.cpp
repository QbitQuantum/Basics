bool CreateJNXJpeg(JPEG_tile_list& tiles, long minx, long maxx, long miny, long maxy, CString mapname, long tileWidth, long tileHeight, int nDatabase, int nDrawOrder)
{

	CProgressWindow wndProgress;
	wndProgress.Initialize();

// ToFix as this ain't right!
double dMetersPerPixel = (double) MyMap.GetMetresPerTile()/MyMap.GetPixelsPerTile();
int nTileWidth = MyMap.GetMetresPerTile();

// JKL's code to create the JPEGs

//	long width, height;
//	long x,y;

	unsigned char * bitmap_memory = NULL;

	long bitmap_width, dest_bitmap_width;
	long bitmap_height, dest_bitmap_height;

	long bitmap_memory_size;
//	long square_width;
//	long square_height;
	unsigned char bitmap_palette[1024];
	long bitmap_palette_length;

	if (minx > maxx) {
		long t = minx;
		minx = maxx;
		maxx = t;
	}
	if (miny > maxy) {
		long t = miny;
		miny = maxy;
		maxy = t;
	}

//	long collar = CalculateCollar(minx*1000, maxx*1000, miny*1000, maxy*1000);
	long collar = CalculateCollar(minx, maxx, miny, maxy);
	minx -= (collar/1000)*1000;
	maxx += (collar/1000)*1000;
	miny -= (collar/1000)*1000;
	maxy += (collar/1000)*1000;

	wndProgress.ResetProgressBar("Tile:", ((maxy-miny)*(maxx-minx))/1000*1000);

	bool successful = false;

	if (nDatabase == DBASE_LOCAL) {

		if (MyMap.GetCountry() == COUNTRY_FR && MyMap.GetProduct() == PRODUCT_02) {

			successful = IGN_ReadTiles(minx, maxx, miny, maxy, wndProgress, 
										bitmap_palette, bitmap_palette_length, 
										bitmap_memory , bitmap_memory_size, 
										bitmap_width, dest_bitmap_width,
										bitmap_height, dest_bitmap_height);
		} else {
			successful = OSPro_ReadTiles(minx, maxx, miny, maxy, wndProgress, 
										bitmap_palette, bitmap_palette_length, 
										bitmap_memory , bitmap_memory_size, 
										bitmap_width, dest_bitmap_width,
										bitmap_height, dest_bitmap_height);
		}

	} else {

		bool b_use_TL3 = nDatabase == DBASE_TRACKLOGS_3;

		successful = ReadTracklogsTile(minx, maxx, miny, maxy, wndProgress, 
										bitmap_palette, bitmap_palette_length, 
										bitmap_memory , bitmap_memory_size, 
										bitmap_width, dest_bitmap_width,
										bitmap_height, dest_bitmap_height,
										b_use_TL3);

	}

//	dest_bitmap_width = 400*(maxx-minx-2*collar/1000);
//	dest_bitmap_height = 400*(maxy-miny-2*collar/1000);

	dest_bitmap_width = nTileWidth*((maxx-minx-(2*collar))/1000);
	dest_bitmap_height = nTileWidth*((maxy-miny-(2*collar))/1000);

	if (!successful) {
		if (bitmap_memory)
			free(bitmap_memory);
		return false;
	}

	if (bitmap_memory == NULL) {
		printf("No images to process\n");
		return false;
	}

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CLSID	encoderClsid;
	// Get the CLSID of the JPEG encoder.
	GetEncoderClsid(L"image/jpeg", &encoderClsid);

	Gdiplus::EncoderParameters encoderParameters;
	encoderParameters.Count = 1;
	ULONG quality = 80;
	encoderParameters.Parameter[0].Guid = Gdiplus::EncoderQuality;
	encoderParameters.Parameter[0].Type = Gdiplus::EncoderParameterValueTypeLong;
	encoderParameters.Parameter[0].NumberOfValues = 1;
	encoderParameters.Parameter[0].Value = &quality;

	// xy
	// 00 10 20 30 40
	// 01 11 21 31 41
	// 02 12 22 32 42
	// 03 13 23 33 43
/*
	minx *= 1000;
	maxx *= 1000;
	miny *= 1000;
	maxy *= 1000;
*/
	double lat,lon;
	OZIGEN_NorthingEasting_to_LatLon(maxy-collar, minx+collar, &lat, &lon);
	double minlat = lat;
	double maxlat = lat;
	double minlon = lon;
	double maxlon = lon;
	OZIGEN_NorthingEasting_to_LatLon(maxy-collar, maxx-collar, &lat, &lon);
	if (lat < minlat) minlat = lat;
	if (lat > maxlat) maxlat = lat;
	if (lon < minlon) minlon = lon;
	if (lon > maxlon) maxlon = lon;
	OZIGEN_NorthingEasting_to_LatLon(miny+collar, minx+collar, &lat, &lon);
	if (lat < minlat) minlat = lat;
	if (lat > maxlat) maxlat = lat;
	if (lon < minlon) minlon = lon;
	if (lon > maxlon) maxlon = lon;
	OZIGEN_NorthingEasting_to_LatLon(miny+collar, maxx-collar, &lat, &lon);
	if (lat < minlat) minlat = lat;
	if (lat > maxlat) maxlat = lat;
	if (lon < minlon) minlon = lon;
	if (lon > maxlon) maxlon = lon;

	OZIGEN_LatLon_to_NorthingEasting(minlat, minlon, &lat, &lon);
	OZIGEN_LatLon_to_NorthingEasting(minlat, maxlon, &lat, &lon);
	OZIGEN_LatLon_to_NorthingEasting(maxlat, maxlon, &lat, &lon);
	OZIGEN_LatLon_to_NorthingEasting(maxlat, minlon, &lat, &lon);


	char jnxName[512];
	GetCurrentDirectory(sizeof(jnxName), jnxName);
	CString Currdir = jnxName;						// Save current directory

	// change directory to %TEMP% and make folder 'files'
	GetTempPath(sizeof(jnxName), jnxName);
	SetCurrentDirectory(jnxName);
	CreateDirectory("files", NULL);

//	sprintf(jnxName, "%s\\%s.kmz", Currdir, mapname);

	long nTilesAcross=(dest_bitmap_width+(tileWidth-1))/tileWidth;
	long nTilesDown=(dest_bitmap_height+(tileHeight-1))/tileHeight;

//	KMZ_tiles tiles; - gone global
	
	long across, down;
	for (across=0; across<nTilesAcross; across++) {
		for (down=0; down<nTilesDown; down++) {

			JPEG_tile * pTile = new JPEG_tile;
			pTile->fname.Format("files/c%02d%02d.jpg", down, across);
			pTile->lat_north = minlat+(maxlat-minlat)*(nTilesDown-down)/nTilesDown;
			pTile->lon_east  = minlon+(maxlon-minlon)*(across+1)/nTilesAcross;
			pTile->lat_south = minlat+(maxlat-minlat)*(nTilesDown-down-1)/nTilesDown;
			pTile->lon_west = minlon+(maxlon-minlon)*across/nTilesAcross;
			pTile->offset_x0 = dest_bitmap_width*across/nTilesAcross;
			pTile->offset_x1 = dest_bitmap_width*(across+1)/nTilesAcross;
			pTile->offset_y0 = dest_bitmap_height*down/nTilesDown;
			pTile->offset_y1 = dest_bitmap_height*(down+1)/nTilesDown;
			tiles.AddTail(pTile);
		}
	}

	Global_AddToResultsWindow("Number of tiles = %d",tiles.GetCount());


// SNL
	wndProgress.ResetProgressBar("JPEG:",tiles.GetCount());

	long tileCount=0;
	long index = 1;
	POSITION pos;
	for (pos=tiles.GetHeadPosition(); pos != NULL; tiles.GetNext(pos)) {
		
		wndProgress.ProgressBar();

		if (wndProgress.m_Cancelled) return false;

		JPEG_tile * pTile = (JPEG_tile *)tiles.GetAt(pos);

		Gdiplus::Rect r(0, 0, pTile->offset_x1-pTile->offset_x0, pTile->offset_y1-pTile->offset_y0);
		Gdiplus::Bitmap bmp(r.GetRight(), r.GetBottom(), PixelFormat24bppRGB );
		Gdiplus::BitmapData bmpData;
		bmp.LockBits(&r, Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite, PixelFormat24bppRGB, &bmpData);

		long x,y;
		for (y=pTile->offset_y0; y<pTile->offset_y1; y++) {
			lat = maxlat-(maxlat-minlat)/dest_bitmap_height*y;
			unsigned char * dest_bitmap_offset = ((unsigned char *)bmpData.Scan0) + bmpData.Stride*(y-pTile->offset_y0);
			for (x=pTile->offset_x0; x<pTile->offset_x1; x++) {
				lon = minlon+(maxlon-minlon)/dest_bitmap_width*x;
				double northing, easting;
				OZIGEN_LatLon_to_NorthingEasting(lat, lon, &northing, &easting);
				northing += 0.5;
				easting += 0.5;
				if (northing < miny || easting < minx || northing > maxy || easting > maxx) {
					// No bitmap data present -- white
					*dest_bitmap_offset++ = 255;
					*dest_bitmap_offset++ = 255;
					*dest_bitmap_offset++ = 255;
				} else {
					// Look up colour of bitmap pixel
					unsigned char * pal = bitmap_palette + 
												4*bitmap_memory[(long)((maxy-northing)/dMetersPerPixel)*bitmap_width +
																(long)((easting-minx)/dMetersPerPixel)];
					*dest_bitmap_offset++ = pal[0];
					*dest_bitmap_offset++ = pal[1];
					*dest_bitmap_offset++ = pal[2];
				}
			}
		}
		bmp.UnlockBits(&bmpData);
		wchar_t wbuffer[64];
		int i;
		for (i=0; i<pTile->fname.GetLength(); i++)
			wbuffer[i] = pTile->fname.GetAt(i);
		wbuffer[i] = 0;
		bmp.Save(wbuffer, &encoderClsid, &encoderParameters);
		tileCount++;
	}


	SetCurrentDirectory(Currdir);
//	tiles.RemoveAll();
/*
	if (nPoints) {
		free(points);
		nPoints = 0;
		points = NULL;
	}
*/

	Gdiplus::GdiplusShutdown(gdiplusToken);

	free(bitmap_memory);


// Next bit from Map2JNX

	// up to five levels. nLevels gives the actual count
	static level_t levels[5];

	// information about all files
	static std::list<file_t> files;

	// the JNX file header to be copied to the outfile
	static jnx_hdr_t jnx_hdr;

	// the tile information table for all 5 levels
	static jnx_tile_t tileTable[JNX_MAX_TILES * 5];

	const uint8_t dummy = 0;
	uint32_t tileTableStart = 0;
	uint32_t tileCnt    = 0;

	const char *jnx_copyright = "Unknown";
	const char *jnx_subscname = "BirdsEye";
	const char *jnx_mapname   = "Unknown";

	char *copyright_buf = NULL;
	char *subscname_buf = NULL;
	char *mapname_buf   = NULL;

	double right    = -180.0;
	double top      =  -90.0;
	double left     =  180.0;
	double bottom   =   90.0;

	double scale = 0.0;

	// Number of used levels
	static int32_t nLevels = 1;

    FILE * fid = fopen(mapname+".jnx","wb");
	if(fid == 0)
    {
		// Failed to create file.
        return false;
    }

// New code writer start
//	POSITION pos;
	for (pos=tiles.GetHeadPosition(); pos != NULL; tiles.GetNext(pos)) {
		JPEG_tile * pTile = (JPEG_tile *)tiles.GetAt(pos);
		if (left > pTile->lon_west)
			left = pTile->lon_west;
		if (right < pTile->lon_east)
			right = pTile->lon_east;
		if (top < pTile->lat_north)
			top = pTile->lat_north;
		if (bottom > pTile->lat_south)
			bottom = pTile->lat_south;
	}
	nLevels = 1;
// New code writer end

	jnx_hdr.zorder  = nDrawOrder;
	jnx_hdr.left    = (int32_t)((left   * 0x7FFFFFFF) / 180);
	jnx_hdr.top     = (int32_t)((top    * 0x7FFFFFFF) / 180);
	jnx_hdr.right   = (int32_t)((right  * 0x7FFFFFFF) / 180);
	jnx_hdr.bottom  = (int32_t)((bottom * 0x7FFFFFFF) / 180);

	jnx_hdr.details = nLevels;

	for(int i=0; i<HEADER_BLOCK_SIZE; i++)
	{
		fwrite(&dummy, sizeof(dummy), 1, fid);
	}
	_fseeki64(fid,0,SEEK_SET);
	fwrite(&jnx_hdr, sizeof(jnx_hdr), 1, fid);

	// get all information to write the table of detail levels and the dummy tile table

	int i=0;

	level_t& level  = levels[i];

	level.nTiles   = tiles.GetCount();
	level.offset   = HEADER_BLOCK_SIZE;		// still has to be offset by complete header
	level.scale    = 1509;

	fwrite(&level.nTiles, sizeof(level.nTiles), 1, fid);
	fwrite(&level.offset, sizeof(level.offset), 1, fid);
	fwrite(&level.scale, sizeof(level.scale), 1, fid);
	fwrite(&level.dummy, sizeof(level.dummy), 1, fid);
	fwrite(jnx_copyright, strlen(jnx_copyright) + 1, 1, fid);

	// printf("\n    Level %i: % 5i tiles, offset %08X, scale: %i, %ix%i", i, level.nTiles, level.offset, level.scale, level.tileSize, level.tileSize);

	// write map loader info block
	uint32_t blockVersion = 0x00000009;
	char GUID[40];
	createGUID(GUID);

	fwrite(&blockVersion, sizeof(blockVersion), 1, fid);
	fwrite(GUID, 37, 1, fid);
	fwrite(jnx_subscname, strlen(jnx_subscname) + 1, 1, fid);
	fwrite(&dummy, sizeof(dummy), 1, fid);
	fwrite(&dummy, sizeof(dummy), 1, fid);
	fwrite(&dummy, sizeof(dummy), 1, fid);
	fwrite(jnx_mapname, strlen(jnx_mapname) + 1, 1, fid);
	fwrite(&nLevels , sizeof(nLevels), 1, fid);

	for(int i = 1; i <= nLevels; i++)
	{
		char str[40];
		sprintf(str,"Level %i", i);
		fwrite(str, strlen(str) + 1, 1, fid);
		fwrite(str, strlen(str) + 1, 1, fid);
		fwrite(jnx_copyright, strlen(jnx_copyright) + 1, 1, fid);
		fwrite(&i,sizeof(i), 1, fid);
	}

    // write dummy tile table
    tileTableStart = HEADER_BLOCK_SIZE;
    _fseeki64(fid, tileTableStart, SEEK_SET);
    fwrite(tileTable, sizeof(jnx_tile_t), tileCount, fid);

// New code writer start
	char TempPath[512];
	GetTempPath(sizeof(TempPath), TempPath);
	CString tPath = TempPath;
	tPath = tPath + "\\";

	wndProgress.ResetProgressBar("JNX:",tiles.GetCount());

	for (pos=tiles.GetHeadPosition(); pos != NULL; tiles.GetNext(pos)) {

		JPEG_tile * pTile = (JPEG_tile *)tiles.GetAt(pos);
//		printf("JPEG %d of %d\r", tileCnt, tiles.GetCount());

       jnx_tile_t& tile = tileTable[tileCnt++];

		tile.left    = (int32_t)(pTile->lon_west * 0x7FFFFFFF / 180);
		tile.top     = (int32_t)(pTile->lat_north * 0x7FFFFFFF / 180);
		tile.right   = (int32_t)(pTile->lon_east * 0x7FFFFFFF / 180);
		tile.bottom  = (int32_t)(pTile->lat_south * 0x7FFFFFFF / 180);

		tile.width  = (uint16_t)(pTile->offset_x1-pTile->offset_x0);
		tile.height = (uint16_t)(pTile->offset_y1-pTile->offset_y0);
		tile.offset = (uint32_t)(_ftelli64(fid) & 0x0FFFFFFFF);
		tile.size   = appendJPG(tPath + pTile->fname, fid);
	}

// New code writer end

    // terminate output file
    fwrite("BirdsEye", 8, 1, fid);

    // write final tile table
    _fseeki64(fid, tileTableStart, SEEK_SET);
    fwrite(tileTable, sizeof(jnx_tile_t), tileCount, fid);
 
	// done
    fclose(fid);

exit_CreateJNXJpeg:

    // Clean up
	if (copyright_buf) free(copyright_buf);
	if (subscname_buf) free(subscname_buf);
	if (mapname_buf) free(mapname_buf);

	//POSITION pos;
	for (pos=tiles.GetHeadPosition(); pos != NULL; tiles.GetNext(pos)) {
		JPEG_tile * pTile = (JPEG_tile *)tiles.GetAt(pos);
		DeleteFile(pTile->fname);
	}

	tiles.RemoveAll();

	return true;
}