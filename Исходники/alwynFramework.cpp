//Inits this.
bool AlwynD3DInterfaceImpl::init()
{
	device->logger->debug("AlwynD3DInterfaceImpl::init\n.");

	adapter = new XFileMeshAdapter(device);

	viewingFrustum = new AlwynD3DViewingFrustum(device);

	//Define and initialise an FPS counter, this uses a high performance memory timer, 
	//which uses very little processing power to compute.
	fpsCounter = new AlwynFPSCounter();

	globalDecals = new GlobalDecals();

	worldScale = new AlwynD3DWorldScale(5.8f);

	//Initialise temp matrices.
	D3DXMatrixIdentity(&tmp);
	D3DXMatrixIdentity(&tmp2);

	//Create xinput devices, for keyboard and gamepad.
	input = new AlwynD3DInput();
	XInputEnable(true);
	input->mouseXY[0] = device->width/2;
	input->mouseXY[1] = device->height/2;

	//Initialise and poll input device.
	device->getInput(input);

	//Initialises the shader.
	if (!initialiseShader(device))
		return false;

	//Initialise and fill decals.
	if (!initDecals(device))
		return false;

	//Initialises the camera/view matrix.
	if (!initCamera(device))
		return false;

	//Initialises the raster states.
	//if (!initRaster(device))
		//return false;

	//Init the font system.
	if (!initFontSystem(device))
		return false;

	//Init lights
	initLights();

	//Framework init;
	if (!frameworkInit(device))
		return false;

	if (adapter)
		delete adapter;
	return true;
}