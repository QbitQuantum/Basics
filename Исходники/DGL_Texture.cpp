	////////////////////////////////////
	// Texture::ImageTGA::Load
	void Texture::ImageTGA::Load(const char* filename)
	{
		int				columns, rows, numPixels;
		unsigned char	*pixbuf;
		int				row, column;
		unsigned char	*buf_p;
		unsigned char	*buffer;
		int				length;
		TargaHeader		targaHeader;
		unsigned char	*targa_rgba;
		unsigned char	tmp[2];
		FILE			*fp;

		// output
		int				width;
		int				height;

		DGL::LogPrint("Loading TGA Image '%s'...",filename);
        
		//
		// load the file
		//
		fp = fopen(filename, "rb");
		if(!fp)
			throw Daher::Exception("File Not Found");
		
		fseek(fp, 0, SEEK_END);
		length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		try {
			buffer = new unsigned char[length];
		} catch (std::bad_alloc) {
			throw Daher::Exception("Cannot allocate memory for TGA texture");
		}

		int result = fread(buffer, length, 1, fp);
		fclose(fp);

		buf_p = buffer;
		targaHeader.idLength = *buf_p++;
		targaHeader.colormapType = *buf_p++;
		targaHeader.imageType = *buf_p++;

		tmp[0] = buf_p[0];
		tmp[1] = buf_p[1];
		targaHeader.colormapIndex = MAKEWORD( tmp[0], tmp[1] );
		buf_p+=2;
		tmp[0] = buf_p[0];
		tmp[1] = buf_p[1];
		targaHeader.colormapLength = MAKEWORD( tmp[0], tmp[1] );
		buf_p+=2;
		targaHeader.colormapSize = *buf_p++;
		targaHeader.xOrigin = MAKEWORD( buf_p[0], buf_p[1] );
		buf_p+=2;
		targaHeader.yOrigin = MAKEWORD( buf_p[0], buf_p[1] );
		buf_p+=2;
		targaHeader.width = MAKEWORD( buf_p[0], buf_p[1] );
		buf_p+=2;
		targaHeader.height = MAKEWORD( buf_p[0], buf_p[1] );
		buf_p+=2;
		targaHeader.pixelSize = *buf_p++;
		targaHeader.attributes = *buf_p++;

		if (targaHeader.imageType!=2 
			&& targaHeader.imageType!=10) 
			throw Daher::Exception("Only type 2 and 10 targa RGB images supported");

		if (targaHeader.colormapType !=0 
			|| (targaHeader.pixelSize!=32 && targaHeader.pixelSize!=24))
			throw Daher::Exception("Only 32 or 24 bit images supported (no colormaps)");

		columns = targaHeader.width;
		rows = targaHeader.height;
		numPixels = columns * rows;

		width = columns;
		height = rows;

		this->data = new unsigned char[numPixels*4];
		targa_rgba = this->data;

		if (targaHeader.idLength != 0)
			buf_p += targaHeader.idLength;  // skip TARGA image comment

		if (targaHeader.imageType==2) {  // Uncompressed, RGB images
			for(row=0; row< rows;  row++) {
				pixbuf = targa_rgba + row*columns*4;
				for(column=0; column<columns; column++) {
					unsigned char red,green,blue,alphabyte;
					switch (targaHeader.pixelSize) {
						case 24:
                            blue = *buf_p++;
							green = *buf_p++;
							red = *buf_p++;
							*pixbuf++ = red;
							*pixbuf++ = green;
							*pixbuf++ = blue;
							*pixbuf++ = 255;
							break;
						case 32:
							blue = *buf_p++;
							green = *buf_p++;
							red = *buf_p++;
							alphabyte = *buf_p++;
							*pixbuf++ = red;
							*pixbuf++ = green;
							*pixbuf++ = blue;
							*pixbuf++ = alphabyte;
							break;
					}
				}
			}
		}
		else if (targaHeader.imageType==10) {   // Runlength encoded RGB images (RLE)
			unsigned char red,green,blue,alphabyte,packetHeader,packetSize,j;
			for(row=0; row<rows; row++) {
				pixbuf = targa_rgba + row*columns*4;
				for(column=0; column<columns; ) {
					packetHeader= *buf_p++;
					packetSize = 1 + (packetHeader & 0x7f);
					if (packetHeader & 0x80) {        // run-length packet
						switch (targaHeader.pixelSize) {
							case 24:
								blue = *buf_p++;
								green = *buf_p++;
								red = *buf_p++;
								alphabyte = 255;
								break;
							case 32:
								blue = *buf_p++;
								green = *buf_p++;
								red = *buf_p++;
								alphabyte = *buf_p++;
								break;
						}
						for(j=0;j<packetSize;j++) {
							*pixbuf++=red;
							*pixbuf++=green;
							*pixbuf++=blue;
							*pixbuf++=alphabyte;
							column++;
							if (column==columns) { // run spans across rows
								column=0;
								if (row<rows)
									row++;
								else
									goto breakOut;
								pixbuf = targa_rgba + row*columns*4;
							}
						}
					} else {                            // non run-length packet
						for(j=0;j<packetSize;j++) {
							switch (targaHeader.pixelSize) {
								case 24:
									blue = *buf_p++;
									green = *buf_p++;
									red = *buf_p++;
									*pixbuf++ = red;
									*pixbuf++ = green;
									*pixbuf++ = blue;
									*pixbuf++ = 255;
									break;
								case 32:
									blue = *buf_p++;
									green = *buf_p++;
									red = *buf_p++;
									alphabyte = *buf_p++;
									*pixbuf++ = red;
									*pixbuf++ = green;
									*pixbuf++ = blue;
									*pixbuf++ = alphabyte;
									break;
							}
							column++;
							if (column==columns) { // pixel packet run spans across rows
								column=0;
								if (row<rows)
									row++;
								else
									goto breakOut;
								pixbuf = targa_rgba + row*columns*4;
							}						
						}
					}
				}
breakOut:;
			}
		}
		delete [] buffer;

		this->components	= 4;
		this->width			= width;
		this->height		= height;
		this->format		= GL_RGBA;
	}