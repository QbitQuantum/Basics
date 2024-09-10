int StartPlugin(){

    //Create an instance of our VB COM object, and execute
	//one of its methods so that it will load up and show a UI
	//for us, then it uses our other exports to access olly plugin API
	//methods

	CLSID      clsid;
	HRESULT	   hr;
    LPOLESTR   p = OLESTR("IDACompare.CPlugin");

    hr = CoInitialize(NULL);

	 hr = CLSIDFromProgID( p , &clsid);
	 if( hr != S_OK  ){
		 MessageBox(0,"Failed to get Clsid from string\n","",0);
		 return 0;
	 }

	 // create an instance and get IDispatch pointer
	 hr =  CoCreateInstance( clsid,
							 NULL,
							 CLSCTX_INPROC_SERVER,
							 IID_IDispatch  ,
							 (void**) &IDisp
						   );

	 if ( hr != S_OK )
	 {
	   MessageBox(0,"CoCreate failed","",0);
	   return 0;
	 }

	 OLECHAR *sMethodName = OLESTR("DoPluginAction");
	 DISPID  dispid; // long integer containing the dispatch ID

	 // Get the Dispatch ID for the method name
	 hr=IDisp->GetIDsOfNames(IID_NULL,&sMethodName,1,LOCALE_USER_DEFAULT,&dispid);
	 if( FAILED(hr) ){
	    MessageBox(0,"GetIDS failed","",0);
		return 0;
	 }

	 DISPPARAMS dispparams;
	 VARIANTARG vararg[1]; //function takes one argument
	 VARIANT    retVal;

	 VariantInit(&vararg[0]);
	 dispparams.rgvarg = &vararg[0];
	 dispparams.cArgs = 0;  // num of args function takes
	 dispparams.cNamedArgs = 0;

	 // and invoke the method
	 hr=IDisp->Invoke( dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparams, &retVal, NULL, NULL);

	 return 0;
}