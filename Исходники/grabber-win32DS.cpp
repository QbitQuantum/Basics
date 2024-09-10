DirectShowScanner::DirectShowScanner() {
   ICreateDevEnum *pDevEnum      = 0;
   int             hr;
   int             devNum;
   char            nameBuf[80];
   
   // Reference:  Pesce, pp 54-56.   

   debug_msg("new DirectShowScanner()\n");

   // Initialize the COM subsystem
   hr=CoInitialize(NULL);
   if (FAILED(hr)) {
	   debug_msg("Failed COM subsystem initialisation.\n");
	   	return;
   }

   // Create a helper object to find the capture devices.
   hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (LPVOID*)&pDevEnum);
   if (FAILED(hr)) {
   		debug_msg("Failed to Create a helper object to find the DS capture devices.\n");
		CoUninitialize();
		return;
   }

   IEnumMoniker *pEnum    = 0;
   IMoniker     *pMoniker = 0;
   IPropertyBag *pPropBag = 0;
   VARIANT      varName;

   // Get an enumerator over video capture filters
   hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
   //showErrorMessage(hr);
   if (FAILED(hr) || pEnum == 0) {
   		debug_msg("Failed to Get an enumerator over DS video capture filters.\n");
		CoUninitialize();
		return;
   }

   // Get the capture filter for each device installed, up to NUM_DEVS devices
   for( devNum=0; devNum < NUM_DEVS; ++devNum) {
      if ( pEnum->Next(1, &pMoniker, NULL) == S_OK ) {

         hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);
	     if (FAILED(hr)) {
			debug_msg("Failed to Get propbag bound to storage on DS dev: %d\n", devNum);
			continue;
		 }
         //showErrorMessage(hr);
         debug_msg("propbag bound to storage ok= %d\n", hr);

         VariantInit(&varName);
         hr = pPropBag->Read(L"FriendlyName", &varName, 0);
		 if (FAILED(hr)) {
			debug_msg("Failed to Get friendly name read on DS dev: %d\n", devNum);
			continue;
		 }
         //showErrorMessage(hr);
         debug_msg("friendly name read ok= %d\n", hr);

         // Need this macro in atlconv.h to go from bStr to char* - msp
         USES_CONVERSION;
         strcpy(nameBuf, W2A(varName.bstrVal));

         debug_msg("DirectShowScanner::DirectShowScanner():  found nameBuf/FriendlyName=%s\n", nameBuf);

         // needs work, but don't add drivers that look like VFW drivers - msp
         if( (strstr(nameBuf, "VFW") == NULL) ) {
            hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void **)(pCaptureFilter+devNum));
            //showErrorMessage(hr);
			if (FAILED(hr)) {
				debug_msg("Failed to Get friendly name read on DS dev: %d\n", devNum);
				continue;
			}
			debug_msg("capture filter bound ok= %d\n", hr);
            devs_[devNum] = new DirectShowDevice(strdup(nameBuf), pCaptureFilter[devNum]);
         } else {
            debug_msg("discarding an apparent VFW device= %s\n", nameBuf);
			devs_[devNum] = NULL;
         }

         VariantClear(&varName);
         pPropBag->Release();
      }
   }

   // Release these objects so COM can release their memory
   pMoniker->Release();
   pEnum->Release();
   pDevEnum->Release();
}