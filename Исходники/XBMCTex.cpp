int main(int argc, char* argv[])
{
  int NoProtect = 0;
  AllowLinear = true;
  double MaxMSE = 4.0;

	CmdLineArgs args;

	if (args.size() == 1)
	{
		Usage();
		return 1;
	}

	const char* InputDir = NULL;
	const char* OutputFilename = "Textures.xpr";

	for (unsigned int i = 1; i < args.size(); ++i)
	{
		if (!stricmp(args[i], "-help") || !stricmp(args[i], "-h") || !stricmp(args[i], "-?"))
		{
			Usage();
			return 1;
		}
		else if (!stricmp(args[i], "-input") || !stricmp(args[i], "-i"))
		{
			InputDir = args[++i];
		}
		else if (!stricmp(args[i], "-output") || !stricmp(args[i], "-o"))
		{
			OutputFilename = args[++i];
		}
    else if (!stricmp(args[i], "-noprotect") || !stricmp(args[i], "-p"))
    {
      NoProtect = 1;
    }
    else if (!stricmp(args[i], "-onlyswizzled") || !stricmp(args[i], "-s"))
    {
      AllowLinear = false;
    }
    else if (!stricmp(args[i], "-quality") || !stricmp(args[i], "-q"))
		{
			++i;
			if (!stricmp(args[i], "min"))
			{
				MaxMSE = DBL_MAX;
			}
			else if (!stricmp(args[i], "low"))
			{
				MaxMSE = 20.0;
			}
			else if (!stricmp(args[i], "normal"))
			{
				MaxMSE = 4.0;
			}
			else if (!stricmp(args[i], "high"))
			{
				MaxMSE = 1.5;
			}
			else if (!stricmp(args[i], "max"))
			{
				MaxMSE = 0.0;
			}
			else
			{
				printf("Unrecognised quality setting: %s\n", args[i]);
			}
		}
		else
		{
			printf("Unrecognised command line flag: %s\n", args[i]);
		}
	}

	// Initialize DirectDraw
	pD3D = Direct3DCreate8(D3D_SDK_VERSION);
	if (pD3D == NULL)
	{
		puts("Cannot init D3D");
		return 1;
	}

	HRESULT hr;
	D3DDISPLAYMODE dispMode;
	D3DPRESENT_PARAMETERS presentParams;

	pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dispMode);

	ZeroMemory(&presentParams, sizeof(presentParams));
	presentParams.Windowed = TRUE;
	presentParams.hDeviceWindow = GetConsoleWindow();
	presentParams.SwapEffect = D3DSWAPEFFECT_COPY;
	presentParams.BackBufferWidth = 8;
	presentParams.BackBufferHeight = 8;
	presentParams.BackBufferFormat = dispMode.Format;

	hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, NULL, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presentParams, &pD3DDevice);
	if (FAILED(hr))
	{
		printf("Cannot init D3D device: %08x\n", hr);
		pD3D->Release();
		return 1;
	}

	char HomeDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, HomeDir);

	XPRFile.OutputBuf = (char*)VirtualAlloc(0, 64 * 1024 * 1024, MEM_RESERVE, PAGE_NOACCESS);
	if (!XPRFile.OutputBuf)
	{
		printf("Memory allocation failure: %08x\n", GetLastError());
		pD3DDevice->Release();
		pD3D->Release();
		return 1;
	}

	Bundler.StartBundle();

	// Scan the input directory (or current dir if false) for media files
	ConvertDirectory(InputDir, NULL, MaxMSE);

	VirtualFree(XPRFile.OutputBuf, 0, MEM_RELEASE);

	pD3DDevice->Release();
	pD3D->Release();

	SetCurrentDirectory(HomeDir);
	DWORD attr = GetFileAttributes(OutputFilename);
	if (attr != -1 && (attr & FILE_ATTRIBUTE_DIRECTORY))
	{
		SetCurrentDirectory(OutputFilename);
		OutputFilename = "Textures.xpr";
	}

	printf("\nWriting bundle: %s", OutputFilename);
  int BundleSize = Bundler.WriteBundle(OutputFilename, NoProtect);
	if (BundleSize == -1)
	{
		printf("\nERROR: %08x\n", GetLastError());
		return 1;
	}

	printf("\nUncompressed texture size: %6dkB\nCompressed texture size: %8dkB\nBundle size:             %8dkB\n\nWasted Pixels: %u/%u (%5.2f%%)\n",
		(UncompressedSize + 1023) / 1024, (((CompressedSize + 1023) / 1024) + 3) & ~3, (BundleSize + 1023) / 1024,
		TotalDstPixels - TotalSrcPixels, TotalDstPixels, 100.f * (float)(TotalDstPixels - TotalSrcPixels) / (float)TotalDstPixels);

	return 0;
}