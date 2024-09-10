// code taken from WCS/VNS VersionGUI.cpp
// memory is allocated with operator new[], caller is responsible for freeing
int LoadJpegResourceAsRGB(unsigned short ImageID, unsigned char *&Red, unsigned char *&Green, unsigned char *&Blue, unsigned long int &Width, unsigned long int &Height)
{
int Success = 0;
HRSRC  ResHandle = NULL;
struct jpeg_decompress_struct cinfo;
struct SW_my_error_mgr jerr;
int row_stride = 0;
unsigned long int InScan, PixelCol;
short Cols, Rows;
unsigned char *InterleaveBuf = NULL, *RBuf, *GBuf, *BBuf;
WORD LOGOID = ImageID;

Width = Height = 0;
Red = Green = Blue = NULL;

// passing NULL as Instance means 'me you moron'
if(ImageJPGRsc = LockResource(LoadResource(NULL, ResHandle = FindResource(NULL, MAKEINTRESOURCE(LOGOID), "JPEGIMAGE"))))
	{
	ImageJPGSize = SizeofResource(NULL, ResHandle);

	cinfo.err = jpeg_std_error((struct jpeg_error_mgr *)&jerr);
	jerr.pub.error_exit = mem_my_JPEGLOADER_error_exit;

	if (setjmp(jerr.setjmp_buffer))
		{
		// If we get here, the JPEG code has signaled an error.
		// We need to clean up the JPEG object, close the input file, and return.
		if(InterleaveBuf) delete [] InterleaveBuf;
		InterleaveBuf = NULL;
		if(!Success)
			{
			delete [] Red; Red = NULL;
			delete [] Green; Green = NULL;
			delete [] Blue; Blue = NULL;
			} // if
		jpeg_destroy_decompress(&cinfo);
		return(Success);
		} // if

	jpeg_create_decompress(&cinfo);
	cinfo.src = &JPEGMemLoader;
	cinfo.src->init_source = mem_init_source;
	cinfo.src->fill_input_buffer = mem_fill_input_buffer;
	cinfo.src->skip_input_data = mem_skip_input_data;
	cinfo.src->resync_to_restart = mem_jpeg_resync_to_restart; /* use default method */
	cinfo.src->term_source = mem_term_source;
	cinfo.src->bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
	cinfo.src->next_input_byte = NULL; /* until buffer loaded */

	jpeg_read_header(&cinfo, TRUE);
	cinfo.out_color_space = JCS_RGB;
	cinfo.dct_method = JDCT_FLOAT;
	jpeg_start_decompress(&cinfo);

	Width = Cols = (short)cinfo.output_width;
	Height = Rows = (short)cinfo.output_height;
	Red = new unsigned char[Cols * Rows];
	Green = new unsigned char[Cols * Rows];
	Blue = new unsigned char[Cols * Rows];
	row_stride = cinfo.output_width * 3;
	InterleaveBuf = new unsigned char[row_stride];
	if(InterleaveBuf && Red && Green && Blue) // everything ok?
		{
		// Clear bitmaps
		memset(Red, 0, Cols * Rows);
		memset(Green, 0, Cols * Rows);
		memset(Blue, 0, Cols * Rows);

		while (cinfo.output_scanline < cinfo.output_height)
			{
			RBuf = &Red[cinfo.output_scanline * Cols];
			GBuf = &Green[cinfo.output_scanline * Cols];
			BBuf = &Blue[cinfo.output_scanline * Cols];
			if(jpeg_read_scanlines(&cinfo, &InterleaveBuf, 1) != 1)
				{
				jpeg_abort_decompress(&cinfo);
				break;
				} // if
			else
				{ // deinterleave
				for(InScan = PixelCol = 0; PixelCol < (unsigned)Cols; PixelCol++)
					{
					RBuf[PixelCol] = InterleaveBuf[InScan++];
					GBuf[PixelCol] = InterleaveBuf[InScan++];
					BBuf[PixelCol] = InterleaveBuf[InScan++];
					} // for
				} // else
			} // while

		if(cinfo.output_scanline == cinfo.output_height)
			{
			Success = 1;
			jpeg_finish_decompress(&cinfo);
			} // if
		} // if

	jpeg_destroy_decompress(&cinfo);

	if(InterleaveBuf) delete [] InterleaveBuf;
	InterleaveBuf = NULL;
	} // if


if(ImageJPGRsc)
	{
	FreeResource(ImageJPGRsc);
	ImageJPGRsc = NULL;
	} // if

return(Success);
} // LoadJpegResourceAsRGB