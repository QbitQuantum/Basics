	int CALLBACK WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
		int argc = __argc;
		char** argv = __argv;

		#if _MSC_VER
			// affects assert.h assert()
			_set_error_mode ( _OUT_TO_MSGBOX );
		    
			// affects crtdbg.h _ASSERT, _ASSERTE, etc
			_CrtSetReportMode ( _CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW | _CRTDBG_MODE_FILE );
			_CrtSetReportFile ( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
		#endif

		return GlutHost ( argc, argv );
	}