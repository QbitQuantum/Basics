void CHwWinCursor::Finish()
{
	if (frames.size()<1)
		return;

	hotx = (hotSpot==CMouseCursor::TopLeft) ? 0 : (short)xmaxsize/2;
	hoty = (hotSpot==CMouseCursor::TopLeft) ? 0 : (short)ymaxsize/2;

	//note: windows only except 16x16,32x32,64x64,etc. (and some more not 2^n ones)
	int squaresize =  next_power_of_2( std::max(xmaxsize,ymaxsize) );

	//resize images
	for (std::vector<ImageData>::iterator it=icons.begin(); it<icons.end(); it++)
		resizeImage(&*it,squaresize,squaresize);

	const int riffsize  = 32 + sizeof(AnihStructure) + (frames.size()+2) * 2 * sizeof(DWORD);
	const int iconssize = icons.size() * (2*sizeof(DWORD) + 3*sizeof(WORD) +
					       sizeof(CursorDirectoryHeader) +
					       sizeof(CursorInfoHeader) +
					       squaresize*squaresize*4 +
					       squaresize*squaresize/8);
	const int totalsize = riffsize + iconssize;
	unsigned char* mem = new unsigned char[ totalsize ];

	unsigned char* curmem = mem;
	DWORD* dwmem;

	//write RIFF header
		strcpy((char*)curmem,"RIFF");	curmem+=4;
		dwmem = (DWORD*)&curmem[0];
		dwmem[0] = totalsize-8;		curmem+=4; //filesize
		strcpy((char*)curmem,"ACON");	curmem+=4;

	//Anih header
		strcpy((char*)curmem,"anih");
		curmem += 4;
		curmem[0] = 36;
		curmem[1] = curmem[2] = curmem[3] = 0;
		curmem += 4;

		AnihStructure anih;
		memset(&anih,0,sizeof(AnihStructure));
		anih.size   = 36;		//anih structure size
		anih.images = image_count;		//number of images
		anih.frames = framerates.size();	//number of frames
		anih.flags  = 0x3L;		//using seq structure and .cur format for saving bmp data
		memcpy(curmem, &anih, sizeof(AnihStructure));
		curmem += sizeof(AnihStructure);

	//LIST + icons
		strcpy((char*)curmem,"LIST");	curmem+=4;
		dwmem = (DWORD*)&curmem[0];
		dwmem[0] = iconssize+4;		curmem+=4;
		strcpy((char*)curmem,"fram");	curmem+=4;

		for (std::vector<ImageData>::iterator it=icons.begin(); it<icons.end(); it++) {
			buildIco(curmem,*it);
			curmem += 2*sizeof(DWORD) + 3*sizeof(WORD)+sizeof(CursorDirectoryHeader)+sizeof(CursorInfoHeader)+squaresize*squaresize*4+squaresize*squaresize/8;
		}

	//SEQ header
		strcpy((char*)curmem,"seq ");
		curmem += 4;
		DWORD* seq = (DWORD*)&curmem[0];
		seq[0] = frames.size()*sizeof(DWORD);
		seq++;
		for (int i=0; i<frames.size(); i++)
			seq[i] = frames.at(i);
		curmem += (frames.size()+1)*sizeof(DWORD);

	//RATE header
		strcpy((char*)curmem,"rate");
		curmem += 4;
		DWORD* rate = (DWORD*)&curmem[0];
		rate[0] = framerates.size()*sizeof(DWORD);
		rate++;
		for (int i=0; i<framerates.size(); i++)
			rate[i] = framerates.at(i);
		curmem += (framerates.size()+1)*sizeof(DWORD);

	/*char fname[256];
	SNPRINTF(fname, sizeof(fname), "cursors/mycursor%d.ani", ++savedcount);
	FILE * pFile = fopen( fname , "wb" );
	fwrite(mem , 1 , curmem-mem, pFile );
	fclose(pFile);*/

	cursor = (HCURSOR)CreateIconFromResourceEx((PBYTE)mem,totalsize,FALSE,0x00030000,squaresize,squaresize,0);

	delete[] mem;
	for (std::vector<ImageData>::iterator it=icons.begin(); it<icons.end(); it++)
		delete[] (*it).data;
	icons.clear();

	//if (cursor==NULL) logOutput.Print("hw cursor failed: x%d y%d",squaresize,squaresize);
}