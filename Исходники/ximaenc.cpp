/**
 * Saves to disk the image in a specific format.
 * \param hFile: file handle (CxMemFile or CxIOFile), with write access.
 * \param imagetype: file format, see ENUM_CXIMAGE_FORMATS
 * \return true if everything is ok
 * \sa ENUM_CXIMAGE_FORMATS
 */
bool CxImage::Encode(CxFile *hFile, uint32_t imagetype)
{

#if CXIMAGE_SUPPORT_BMP
	if (CXIMAGE_FORMAT_BMP==imagetype){
		CxImageBMP *newima = new CxImageBMP;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_ICO
	if (CXIMAGE_FORMAT_ICO==imagetype){
		CxImageICO *newima = new CxImageICO;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_TIF
	if (CXIMAGE_FORMAT_TIF==imagetype){
		CxImageTIF *newima = new CxImageTIF;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_JPG
	if (CXIMAGE_FORMAT_JPG==imagetype){
		CxImageJPG *newima = new CxImageJPG;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_GIF
	if (CXIMAGE_FORMAT_GIF==imagetype){
		CxImageGIF *newima = new CxImageGIF;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_PNG
	if (CXIMAGE_FORMAT_PNG==imagetype){
		CxImagePNG *newima = new CxImagePNG;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_MNG
	if (CXIMAGE_FORMAT_MNG==imagetype){
		CxImageMNG *newima = new CxImageMNG;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_TGA
	if (CXIMAGE_FORMAT_TGA==imagetype){
		CxImageTGA *newima = new CxImageTGA;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_PCX
	if (CXIMAGE_FORMAT_PCX==imagetype){
		CxImagePCX *newima = new CxImagePCX;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_WBMP
	if (CXIMAGE_FORMAT_WBMP==imagetype){
		CxImageWBMP *newima = new CxImageWBMP;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_WMF && CXIMAGE_SUPPORT_WINDOWS // <vho> - WMF/EMF support
	if (CXIMAGE_FORMAT_WMF==imagetype){
		CxImageWMF *newima = new CxImageWMF;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_JBG
	if (CXIMAGE_FORMAT_JBG==imagetype){
		CxImageJBG *newima = new CxImageJBG;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_JASPER
	if (
 #if	CXIMAGE_SUPPORT_JP2
		CXIMAGE_FORMAT_JP2==imagetype ||
 #endif
 #if	CXIMAGE_SUPPORT_JPC
		CXIMAGE_FORMAT_JPC==imagetype ||
 #endif
 #if	CXIMAGE_SUPPORT_PGX
		CXIMAGE_FORMAT_PGX==imagetype ||
 #endif
 #if	CXIMAGE_SUPPORT_PNM
		CXIMAGE_FORMAT_PNM==imagetype ||
 #endif
 #if	CXIMAGE_SUPPORT_RAS
		CXIMAGE_FORMAT_RAS==imagetype ||
 #endif
		 false ){
		CxImageJAS *newima = new CxImageJAS;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile,imagetype)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif

#if CXIMAGE_SUPPORT_SKA
	if (CXIMAGE_FORMAT_SKA==imagetype){
		CxImageSKA *newima = new CxImageSKA;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif

#if CXIMAGE_SUPPORT_RAW
	if (CXIMAGE_FORMAT_RAW==imagetype){
		CxImageRAW *newima = new CxImageRAW;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif

#if CXIMAGE_SUPPORT_PSD
	if (CXIMAGE_FORMAT_PSD==imagetype){
		CxImagePSD *newima = new CxImagePSD;
		if (!newima) return false;
		newima->Ghost(this);
		if (newima->Encode(hFile)){
			delete newima;
			return true;
		} else {
			strcpy(info.szLastError,newima->GetLastError());
			delete newima;
			return false;
		}
	}
#endif

	strcpy(info.szLastError,"Encode: Unknown format");
	return false;
}