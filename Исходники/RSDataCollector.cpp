/*******************************************************************************
Main entry point. Here we demonstrate, after some initial housekeeping, how to
initialize the camera, start streaming, grab samples, and process them.
*******************************************************************************/
int main(int argc, char *argv[]) {
	if (!ProcessCmdArgs(argc, argv)) {
		return 1;
	}

	// Check / create file directories
	if (xdmPath != nullptr) {
		if (_mkdir(xdmPath) != 0 && errno != EEXIST){
			fprintf(stderr, "Error: Invalid XDM path. Error %d\n", errno);
			fprintf(stderr, "Terminate? [Y/n]\n");
			char choice = _getch();
			if (choice != 'n' && choice != 'N') {
				return ERROR_FILE;
			}
			xdmPath = nullptr;
		}
		else {
			// Remove any trailing '\' in the path since we'll add it later.
			if (xdmPath[strlen(xdmPath) - 1] == '\\')
				xdmPath[strlen(xdmPath) - 1] = '0';
		}
	}
	if (bufPath != nullptr) {
		if (_mkdir(bufPath) != 0 && errno != EEXIST){
			fprintf(stderr, "Error: Invalid Buffer path. Error %d\n", errno);
			fprintf(stderr, "Terminate? [Y/n]\n");
			char choice = _getch();
			if (choice != 'n' && choice != 'N') {
				return ERROR_FILE;
			}
			bufPath = nullptr;
		}
		else {
			// Remove any trailing '\' in the path since we'll add it later.
			if (bufPath[strlen(bufPath) - 1] == '\\')
				bufPath[strlen(bufPath) - 1] = '0';
		}
	}

	// Start timer for total test execution
	unsigned long long programStart = GetTickCount64();
	
	// Initialize camera and streams
	if (verbose) fprintf_s(stdout, "Initializing camera...\n");
	// The Sense Manager is the root object for interacting with the camera.
	PXCSenseManager *senseManager = nullptr;
	senseManager = PXCSenseManager::CreateInstance();
	if (!senseManager) {
		fprintf_s(stderr, "Unable to create the PXCSenseManager\n");
		return ERROR_CAMERA;
	}

	// When enabling the streams (color and depth), the parameters must match
	// the capabilities of the camera. For example, 60fps for color will fail
	// on the DS4 / R200.
	// Here we're hard-coding the resolution and frame rate
	senseManager->EnableStream(PXCCapture::STREAM_TYPE_COLOR, 320, 240, 30);
	senseManager->EnableStream(PXCCapture::STREAM_TYPE_DEPTH, 320, 240, 30);

	// Initialize the PXCSenseManager
	pxcStatus camStatus;
	camStatus = senseManager->Init();
	if (camStatus != PXC_STATUS_NO_ERROR) {
		fprintf_s(stderr, "Unable to initizlize PXCSenseManager\n");
		senseManager->Release();
		return ERROR_CAMERA;
	}
	
	PXCImage *colorImage;
	PXCImage *depthImage;
	PXCPhoto *xdmPhoto = senseManager->QuerySession()->CreatePhoto();

	// These two objects come from the Intel RealSense SDK helper for rendering
	// camera data. Any rendering technique could be used or omitted if no 
	// visual feedback is desired.
	UtilRender *renderColor = new UtilRender(L"COLOR STREAM");
	UtilRender *renderDepth = new UtilRender(L"DEPTH STREAM");
	
	// Start test
	if (verbose) fprintf_s(stdout, "Running...\n");
	// This section may be wrapped in additional code to automate 
	// repetitive tests. Closure provided just for convenience.
	{ // Beginning of single test block
		unsigned long totalFrames = 0;
		unsigned long long streamStart = GetTickCount64();
		for (unsigned int i = 0; i < framesPerTest; i++) {
			// Passing 'true' to AcquireFrame blocks until all streams are 
			// ready (depth and color).  Passing 'false' will result in 
			// frames unaligned in time.
			camStatus = senseManager->AcquireFrame(true);
			if (camStatus < PXC_STATUS_NO_ERROR) {
				fprintf_s(stderr, "Error acquiring frame: %f\n", camStatus);
				break;
			}
			// Retrieve all available image samples
			PXCCapture::Sample *sample = senseManager->QuerySample();
			if (sample == NULL) {
				fprintf_s(stderr, "Sample unavailable\n");
			}
			else {
				totalFrames++;

				colorImage = sample->color;
				depthImage = sample->depth;
				// Render the frames (not necessary)
				if (!renderColor->RenderFrame(colorImage)) break;
				if (!renderDepth->RenderFrame(depthImage)) break;

				// Save data if requested
				wchar_t filePath[MAXPATH];
				char fileName[18];
				TimeStampString(fileName);
				if (xdmPath != nullptr) { // Save XDM image
					swprintf_s(filePath, MAXPATH, L"%S\\%S%S", 
						xdmPath, 
						fileName,
						xdmExt);
					xdmPhoto->ImportFromPreviewSample(sample);
					pxcStatus saveStatus = xdmPhoto->SaveXDM(filePath);
					if (saveStatus != PXC_STATUS_NO_ERROR)
						fprintf_s(stderr, "Error: SaveXDM\n");
				}
				if (bufPath != NULL) { // Save depth buffer
					swprintf_s(filePath, MAXPATH, L"%S\\%S%S", 
						bufPath, fileName, depBufExt);
					// The WriteDepthBuf function has a lot of detail about
					// accessing image data and should be examined.
					if (!WriteDepthBuf(depthImage, filePath)) {
						fprintf(stderr, "Error: WriteDepthBuf\n");
					}
				}
			}

			// Unlock the current frame to fetch the next one
			senseManager->ReleaseFrame();

		}

		float frameRate = (float)totalFrames /
			((float)(GetTickCount64() - streamStart) / 1000);
		if (verbose) fprintf_s(stdout, "Frame Rate: %.2f\n", frameRate);
	} // End of single test block

	// Wrap up
	if(verbose) fprintf_s(stdout, "Finished in %llu seconds.\n",
		(GetTickCount64() - programStart) / 1000);

	delete renderColor;
	delete renderDepth;
	xdmPhoto->Release();
	if(senseManager != nullptr) senseManager->Release();

	return 0;
}