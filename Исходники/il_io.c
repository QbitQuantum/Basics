ILboolean ILAPIENTRY ilLoad(ILenum Type, const ILstring FileName) {
#ifndef _UNICODE
	if (FileName == NULL || strlen(FileName) < 1) {
#else
	char AnsiName[512];
	if (FileName == NULL || wcslen(FileName) < 1) {
#endif//_UNICODE
		ilSetError(IL_INVALID_PARAM);
		return IL_FALSE;
	}

	switch (Type)
	{
		case IL_TYPE_UNKNOWN:
			return ilLoadImage(FileName);

		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilLoadTarga(FileName);
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilLoadJpeg(FileName);
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilLoadDds(FileName);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilLoadPng(FileName);
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilLoadBmp(FileName);
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			return ilLoadGif(FileName);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilLoadHdr(FileName);
		#endif

		#ifndef IL_NO_CUT
		case IL_CUT:
			return ilLoadCut(FileName);
		#endif

		#ifndef IL_NO_DOOM
		case IL_DOOM:
			return ilLoadDoom(FileName);
		case IL_DOOM_FLAT:
			return ilLoadDoomFlat(FileName);
		#endif

		#ifndef IL_NO_ICO
		case IL_ICO:
			return ilLoadIcon(FileName);
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			return ilLoadLif(FileName);
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			return ilLoadMdl(FileName);
		#endif

		#ifndef IL_NO_MNG
		case IL_MNG:
			return ilLoadMng(FileName);
		#endif

		#ifndef IL_NO_PCD
		case IL_PCD:
			return IL_FALSE;//ilLoadPcd(FileName);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilLoadPcx(FileName);
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			return ilLoadPic(FileName);
		#endif

		#ifndef IL_NO_PIX
		case IL_PIX:
			return ilLoadPix(FileName);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilLoadPnm(FileName);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilLoadPsd(FileName);
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			return ilLoadPsp(FileName);
		#endif

		#ifndef IL_NO_PXR
		case IL_PXR:
			return ilLoadPxr(FileName);
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			return ilLoadRaw(FileName);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilLoadSgi(FileName);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			#ifndef _UNICODE
				return ilLoadTiff(FileName);
			#else
				wcstombs(AnsiName, FileName, 512);
				//WideCharToMultiByte(CP_ACP, 0, FileName, -1, AnsiName, 512, NULL, NULL);
				return ilLoadTiff(AnsiName);
			#endif//_UNICODE
		#endif

		#ifndef IL_NO_WAL
		case IL_WAL:
			return ilLoadWal(FileName);
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			return ilLoadXpm(FileName);
		#endif
	}

	ilSetError(IL_INVALID_ENUM);
	return IL_FALSE;
}


ILboolean ILAPIENTRY ilLoadF(ILenum Type, ILHANDLE File)
{
	if (File == NULL) {
		ilSetError(IL_INVALID_PARAM);
		return IL_FALSE;
	}

	if (Type == IL_TYPE_UNKNOWN)
		Type = ilDetermineTypeF(File);
	
	switch (Type)
	{
		case IL_TYPE_UNKNOWN:
			return IL_FALSE;

		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilLoadTargaF(File);
		#endif

		#ifndef IL_NO_JPG
			#ifndef IL_USE_IJL
			case IL_JPG:
				return ilLoadJpegF(File);
			#endif
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilLoadDdsF(File);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilLoadPngF(File);
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilLoadBmpF(File);
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			return ilLoadGifF(File);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilLoadHdrF(File);
		#endif

		#ifndef IL_NO_CUT
		case IL_CUT:
			return ilLoadCutF(File);
		#endif

		#ifndef IL_NO_DOOM
		case IL_DOOM:
			return ilLoadDoomF(File);
		case IL_DOOM_FLAT:
			return ilLoadDoomFlatF(File);
		#endif

		#ifndef IL_NO_ICO
		case IL_ICO:
			return ilLoadIconF(File);
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			return ilLoadLifF(File);
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			return ilLoadMdlF(File);
		#endif

		#ifndef IL_NO_MNG
		case IL_MNG:
			return ilLoadMngF(File);
		#endif

		#ifndef IL_NO_PCD
		case IL_PCD:
			return IL_FALSE;//return ilLoadPcdF(File);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilLoadPcxF(File);
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			return ilLoadPicF(File);
		#endif

		#ifndef IL_NO_PIX
		case IL_PIX:
			return ilLoadPixF(File);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilLoadPnmF(File);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilLoadPsdF(File);
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			return ilLoadPspF(File);
		#endif

		#ifndef IL_NO_PXR
		case IL_PXR:
			return ilLoadPxrF(File);
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			return ilLoadRawF(File);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilLoadSgiF(File);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilLoadTiffF(File);
		#endif

		#ifndef IL_NO_WAL
		case IL_WAL:
			return ilLoadWalF(File);
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			return ilLoadXpmF(File);
		#endif
	}

	ilSetError(IL_INVALID_ENUM);
	return IL_FALSE;
}


ILboolean ILAPIENTRY ilLoadL(ILenum Type, const ILvoid *Lump, ILuint Size) {
	if (Lump == NULL || Size == 0) {
		ilSetError(IL_INVALID_PARAM);
		return IL_FALSE;
	}

	if (Type == IL_TYPE_UNKNOWN)
		Type = ilDetermineTypeL(Lump, Size);
	
	switch (Type)
	{
		case IL_TYPE_UNKNOWN:
			return IL_FALSE;

		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilLoadTargaL(Lump, Size);
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilLoadJpegL(Lump, Size);
		#endif

		#ifndef IL_NO_DDS
		case IL_DDS:
			return ilLoadDdsL(Lump, Size);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilLoadPngL(Lump, Size);
		#endif

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilLoadBmpL(Lump, Size);
		#endif

		#ifndef IL_NO_GIF
		case IL_GIF:
			return ilLoadGifL(Lump, Size);
		#endif

		#ifndef IL_NO_HDR
		case IL_HDR:
			return ilLoadHdrL(Lump, Size);
		#endif

		#ifndef IL_NO_CUT
		case IL_CUT:
			return ilLoadCutL(Lump, Size);
		#endif

		#ifndef IL_NO_DOOM
		case IL_DOOM:
			return ilLoadDoomL(Lump, Size);
		case IL_DOOM_FLAT:
			return ilLoadDoomFlatL(Lump, Size);
		#endif

		#ifndef IL_NO_ICO
		case IL_ICO:
			return ilLoadIconL(Lump, Size);
		#endif

		#ifndef IL_NO_LIF
		case IL_LIF:
			return ilLoadLifL(Lump, Size);
		#endif

		#ifndef IL_NO_MDL
		case IL_MDL:
			return ilLoadMdlL(Lump, Size);
		#endif

		#ifndef IL_NO_MNG
		case IL_MNG:
			return ilLoadMngL(Lump, Size);
		#endif

		#ifndef IL_NO_PCD
		case IL_PCD:
			return IL_FALSE;//return ilLoadPcdL(Lump, Size);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilLoadPcxL(Lump, Size);
		#endif

		#ifndef IL_NO_PIC
		case IL_PIC:
			return ilLoadPicL(Lump, Size);
		#endif

		#ifndef IL_NO_PIX
		case IL_PIX:
			return ilLoadPixL(Lump, Size);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilLoadPnmL(Lump, Size);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilLoadPsdL(Lump, Size);
		#endif

		#ifndef IL_NO_PSP
		case IL_PSP:
			return ilLoadPspL(Lump, Size);
		#endif

		#ifndef IL_NO_PXR
		case IL_PXR:
			return ilLoadPxrL(Lump, Size);
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			return ilLoadRawL(Lump, Size);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilLoadSgiL(Lump, Size);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilLoadTiffL(Lump, Size);
		#endif

		#ifndef IL_NO_WAL
		case IL_WAL:
			return ilLoadWalL(Lump, Size);
		#endif

		#ifndef IL_NO_XPM
		case IL_XPM:
			return ilLoadXpmL(Lump, Size);
		#endif
	}

	ilSetError(IL_INVALID_ENUM);
	return IL_FALSE;
}


//! Attempts to load an image with various different methods before failing - very generic.
ILboolean ILAPIENTRY ilLoadImage(const ILstring FileName)
{
	ILstring	Ext = iGetExtension(FileName);
	ILenum		Type;

	if (iCurImage == NULL) {
		ilSetError(IL_ILLEGAL_OPERATION);
		return IL_FALSE;
	}

#ifndef _UNICODE
	if (FileName == NULL || strlen(FileName) < 1) {
#else
	if (FileName == NULL || wcslen(FileName) < 1) {
#endif//_UNICODE
		ilSetError(IL_INVALID_PARAM);
		return IL_FALSE;
	}

	// Try registered procedures first (so users can override default lib functions).
	if (Ext) {
		if (iRegisterLoad(FileName))
			return IL_TRUE;

		#ifndef IL_NO_TGA
		if (!iStrCmp(Ext, IL_TEXT("tga")) || !iStrCmp(Ext, IL_TEXT("vda")) ||
			!iStrCmp(Ext, IL_TEXT("icb")) || !iStrCmp(Ext, IL_TEXT("vst"))) {
			return ilLoadTarga(FileName);
		}
		#endif

		#ifndef IL_NO_JPG
		if (!iStrCmp(Ext, IL_TEXT("jpg")) || !iStrCmp(Ext, IL_TEXT("jpe")) ||
			!iStrCmp(Ext, IL_TEXT("jpeg"))) {
			return ilLoadJpeg(FileName);
		}
		#endif

		#ifndef IL_NO_DDS
		if (!iStrCmp(Ext, IL_TEXT("dds"))) {
			return ilLoadDds(FileName);
		}
		#endif

		#ifndef IL_NO_PNG
		if (!iStrCmp(Ext, IL_TEXT("png"))) {
			return ilLoadPng(FileName);
		}
		#endif

		#ifndef IL_NO_BMP
		if (!iStrCmp(Ext, IL_TEXT("bmp")) || !iStrCmp(Ext, IL_TEXT("dib"))) {
			return ilLoadBmp(FileName);
		}
		#endif

		#ifndef IL_NO_GIF
		if (!iStrCmp(Ext, IL_TEXT("gif"))) {
			return ilLoadGif(FileName);
		}
		#endif

		#ifndef IL_NO_HDR
		if (!iStrCmp(Ext, IL_TEXT("hdr"))) {
			return ilLoadHdr(FileName);
		}
		#endif

		#ifndef IL_NO_CUT
		if (!iStrCmp(Ext, IL_TEXT("cut"))) {
			return ilLoadCut(FileName);
		}
		#endif

		#ifndef IL_NO_DCX
		if (!iStrCmp(Ext, IL_TEXT("dcx"))) {
			return ilLoadDcx(FileName);
		}
		#endif

		#ifndef IL_NO_ICO
		if (!iStrCmp(Ext, IL_TEXT("ico")) || !iStrCmp(Ext, IL_TEXT("cur"))) {
			return ilLoadIcon(FileName);
		}
		#endif

		#ifndef IL_NO_LIF
		if (!iStrCmp(Ext, IL_TEXT("lif"))) {
			return ilLoadLif(FileName);
		}
		#endif

		#ifndef IL_NO_MDL
		if (!iStrCmp(Ext, IL_TEXT("mdl"))) {
			return ilLoadMdl(FileName);
		}
		#endif

		#ifndef IL_NO_MNG
		if (!iStrCmp(Ext, IL_TEXT("mng")) || !iStrCmp(Ext, IL_TEXT("jng"))) {
			return ilLoadMng(FileName);
		}
		#endif

		#ifndef IL_NO_PCD
		if (!iStrCmp(Ext, IL_TEXT("pcd"))) {
			return IL_FALSE;//return ilLoadPcd(FileName);
		}
		#endif

		#ifndef IL_NO_PCX
		if (!iStrCmp(Ext, IL_TEXT("pcx"))) {
			return ilLoadPcx(FileName);
		}
		#endif

		#ifndef IL_NO_PIC
		if (!iStrCmp(Ext, IL_TEXT("pic"))) {
			return ilLoadPic(FileName);
		}
		#endif

		#ifndef IL_NO_PIX
		if (!iStrCmp(Ext, IL_TEXT("pix"))) {
			return ilLoadPix(FileName);
		}
		#endif

		#ifndef IL_NO_PNM
		if (!iStrCmp(Ext, IL_TEXT("pbm"))) {
			return ilLoadPnm(FileName);
		}
		if (!iStrCmp(Ext, IL_TEXT("pgm"))) {
			return ilLoadPnm(FileName);
		}
		if (!iStrCmp(Ext, IL_TEXT("pnm"))) {
			return ilLoadPnm(FileName);
		}
		if (!iStrCmp(Ext, IL_TEXT("ppm"))) {
			return ilLoadPnm(FileName);
		}
		#endif

		#ifndef IL_NO_PSD
		if (!iStrCmp(Ext, IL_TEXT("psd")) || !iStrCmp(Ext, IL_TEXT("pdd"))) {
			return ilLoadPsd(FileName);
		}
		#endif

		#ifndef IL_NO_PSP
		if (!iStrCmp(Ext, IL_TEXT("psp"))) {
			return ilLoadPsp(FileName);
		}
		#endif

		#ifndef IL_NO_PXR
		if (!iStrCmp(Ext, IL_TEXT("pxr"))) {
			return ilLoadPxr(FileName);
		}
		#endif

		#ifndef IL_NO_SGI
		if (!iStrCmp(Ext, IL_TEXT("sgi")) || !iStrCmp(Ext, IL_TEXT("bw")) ||
			!iStrCmp(Ext, IL_TEXT("rgb")) || !iStrCmp(Ext, IL_TEXT("rgba"))) {
			return ilLoadSgi(FileName);
		}
		#endif

		#ifndef IL_NO_TIF
		if (!iStrCmp(Ext, IL_TEXT("tif")) || !iStrCmp(Ext, IL_TEXT("tiff"))) {
			return ilLoadTiff(FileName);
		}
		#endif

		#ifndef IL_NO_WAL
		if (!iStrCmp(Ext, IL_TEXT("wal"))) {
			return ilLoadWal(FileName);
		}
		#endif

		#ifndef IL_NO_XPM
		if (!iStrCmp(Ext, IL_TEXT("xpm"))) {
			return ilLoadXpm(FileName);
		}
		#endif
	}

	// As a last-ditch effort, try to identify the image
	Type = ilDetermineType(FileName);
	if (Type == IL_TYPE_UNKNOWN)
		return IL_FALSE;
	return ilLoad(Type, FileName);
}


ILboolean ILAPIENTRY ilSave(ILenum Type, ILstring FileName)
{
	switch (Type)
	{
		case IL_TYPE_UNKNOWN:
			return ilSaveImage(FileName);

		#ifndef IL_NO_BMP
		case IL_BMP:
			return ilSaveBmp(FileName);
		#endif

		#ifndef IL_NO_CHEAD
		case IL_CHEAD:
			return ilSaveCHeader(FileName, "IL_IMAGE");
		#endif

		#ifndef IL_NO_JPG
		case IL_JPG:
			return ilSaveJpeg(FileName);
		#endif

		#ifndef IL_NO_PCX
		case IL_PCX:
			return ilSavePcx(FileName);
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			return ilSavePng(FileName);
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			return ilSavePnm(FileName);
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			return ilSavePsd(FileName);
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			return ilSaveRaw(FileName);
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			return ilSaveSgi(FileName);
		#endif

		#ifndef IL_NO_TGA
		case IL_TGA:
			return ilSaveTarga(FileName);
		#endif

		#ifndef IL_NO_TIF
		case IL_TIF:
			return ilSaveTiff(FileName);
		#endif

		case IL_JASC_PAL:
			return ilSaveJascPal(FileName);
	}

	ilSetError(IL_INVALID_ENUM);
	return IL_FALSE;
}


ILuint ILAPIENTRY ilSaveF(ILenum Type, ILHANDLE File)
{
	ILboolean Ret;

	if (File == NULL) {
		ilSetError(IL_INVALID_PARAM);
		return 0;
	}

	switch (Type)
	{
		#ifndef IL_NO_BMP
		case IL_BMP:
			Ret = ilSaveBmpF(File);
			break;
		#endif

		#ifndef IL_NO_JPG
			#ifndef IL_USE_IJL
			case IL_JPG:
				Ret = ilSaveJpegF(File);
				break;
			#endif
		#endif

		#ifndef IL_NO_PNM
		case IL_PNM:
			Ret = ilSavePnmF(File);
			break;
		#endif

		#ifndef IL_NO_PNG
		case IL_PNG:
			Ret = ilSavePngF(File);
			break;	
		#endif

		#ifndef IL_NO_PSD
		case IL_PSD:
			Ret = ilSavePsdF(File);
			break;
		#endif

		#ifndef IL_NO_RAW
		case IL_RAW:
			Ret = ilSaveRawF(File);
			break;
		#endif

		#ifndef IL_NO_SGI
		case IL_SGI:
			Ret = ilSaveSgiF(File);
			break;
		#endif

		#ifndef IL_NO_TGA
		case IL_TGA:
			Ret = ilSaveTargaF(File);
			break;
		#endif

		/*#ifndef IL_NO_TIF
		case IL_TIF:
			Ret = ilSaveTiffF(File);
			break;
		#endif*/

		default:
			ilSetError(IL_INVALID_ENUM);
			return 0;
	}

	if (Ret == IL_FALSE)
		return 0;

	return itell();
}