HANDLE Test_WriteTestFile
(
 char		*runfile,               /* data file to write to. */
 void huge	*big_buffer,            /* buffer holding data.   */
 int byte_size_of_pixel             /* size of a pixel in bytes */
)

{
	DWORD BytesToWrite = 4100;
	LPDWORD BytesWritten;
	DWORD temp;

    HANDLE fileptr = NULL;				   /* pointer to file		 */
    CSMAHead * header;

	BytesWritten = &temp;
    fileptr = CreateFile( runfile,
						  GENERIC_WRITE,
						  FILE_SHARE_WRITE,
						  0,
						  CREATE_ALWAYS,
						  FILE_ATTRIBUTE_NORMAL,
						  0);

    header = new CSMAHead;
    memset( header, 0, 4100 );
    /*  fill in some of the header  */
    header->noscan = -1;
    
	header->datatype = 3;  //unsigned integer
    
	header->ydim		= PICM_Get_pixeldimension_y();
    /* if multiple frame, * frameNum */
	header->lnoscan		= header->ydim;  
	header->xdim		= PICM_Get_pixeldimension_x();
    header->scramble = 1;
    header->lastvalue   = 0x5555;
	header->WinView_id  = 0x1234567;
	header->file_header_ver = HEADER_VERSION;
    
   
    /*  write CSMA HEADER to Output File  */
	WriteFile ( fileptr,
				(LPCVOID) header,
				BytesToWrite,
				BytesWritten,
				0);

    /*  release Header Memory  */
    delete ( header ); 

	/*  Generate a TEST CSMA DATA file  */
    LPCVOID address;

	BytesWritten = &temp;

    /*  write data to Output File  */
    address = (LPCVOID)big_buffer;

	BytesToWrite =	(long)PICM_Get_pixeldimension_x() * 
					(long)byte_size_of_pixel * 
					(long)PICM_Get_pixeldimension_y();

	WriteFile ( fileptr,
				address,
				BytesToWrite,
				BytesWritten,
				0);

    CloseHandle( fileptr );

	return fileptr;
}