//////////////////////////////////////////////////////////////////////////
//  This is the routine where we create the data being output by the Virtual
//  Camera device.
//////////////////////////////////////////////////////////////////////////
bool badRes = false;
bool badServer = false;
HANDLE fileHandle = NULL;
void* file;
int frameWidth = 640;
int frameHeight = 480;
int fileSize = (1280 * 1024 * 3) + 3;
int serverDown = 0;

HMODULE thisLibrary = LoadLibrary(L"NiVirtualCamFilter.dll");
HRSRC errorBitmapInfo = FindResource(thisLibrary, MAKEINTRESOURCE(4), MAKEINTRESOURCE(10));
int errorBitmapSize = SizeofResource(thisLibrary, errorBitmapInfo);
HGLOBAL errorBitmap = LoadResource(thisLibrary, errorBitmapInfo);
void* errorBitmapData = LockResource(errorBitmap);
bool errorBitmapLoaded = errorBitmapSize > 0;
HRESULT CKCamStream::FillBuffer(IMediaSample *pms)
{
	// Init setting object
	if (fileHandle == NULL){
		fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"OpenNiVirtualCamFrameData");
		if (fileHandle == NULL){
			//fileHandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, FILE_MAP_ALL_ACCESS, 0, fileSize, L"OpenNiVirtualCamFrameData");
			if (fileHandle == NULL && !badServer){
				badServer = true;
                MessageBox(NULL, L"Can not connect to the Server; please make sure that NiVirtualCam Controller Application is running. We keep trying until you open it.", L"Connection failed", MB_ICONWARNING);
            }
		}else