// EXPORT FUNCTION:Init()
__declspec(dllexport) bool __stdcall OpenNIInit( HWND hWnd, bool EngFlag, LPDIRECT3DDEVICE9 lpDevice, WCHAR* f_path, CHAR* onifilename )
{
	TrackingF=false;
	for( int i = 0; i < 15; ++ i )
		TrCount[i] = 0;

	SetCurrentDirectoryW( f_path );

	if( nite::NiTE::initialize() == nite::STATUS_OK )
	{
		if( g_UserTracker.create() == nite::STATUS_OK )
		{
			nite::UserTrackerFrameRef mUserFrame;
			if( g_UserTracker.readFrame( &mUserFrame ) == nite::STATUS_OK )
			{
				openni::VideoFrameRef mDepthMap = mUserFrame.getDepthFrame();
				int x = mDepthMap.getWidth(),
					y = mDepthMap.getHeight();
				
				texWidth =  getClosestPowerOfTwo( x / 4 );
				texHeight = getClosestPowerOfTwo( y / 4 );
				
				if( FAILED( lpDevice->CreateTexture( texWidth, texHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &DepthTex, NULL ) ) )
				{
					MessageBox( hWnd, L"Cannot create depth texture", L"NiTE2", MB_OK );
					OpenNIClean();
					return false;
				}

				return true;
			}
			else
			{
				printError( hWnd, "UserTracker.readFrame" );
				MessageBox( hWnd, L"Cannot read user tracker frame", L"NiTE2", MB_OK );
				OpenNIClean();
				return false;
			}
		}
		else
		{
			printError( hWnd, "UserTracker.create" );
			MessageBox( hWnd, L"Cannot create user tracker", L"NiTE2", MB_OK );
			OpenNIClean();
			return false;
		}
	}
	else
	{
		printError( hWnd, "Init" );
		MessageBox( hWnd, L"Cannot initial NiTE", L"NiTE2", MB_OK );
		return false;
	}
}