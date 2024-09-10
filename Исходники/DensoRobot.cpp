	void DensoRobot::Start()
	{
		/* Start the motor */
		CComVariant pVal; // probably empty
		hr = pRobot->Execute(CComBSTR(L"Motor"), CComVariant(L"1"), &pVal);
		if(FAILED(hr)) throw exception("Failed to start the robot motor!");

		/* Set the external robot speed TO DO*/ 
		CComVariant parameters; 
        parameters.vt = VT_ARRAY | VT_VARIANT; 

        SAFEARRAYBOUND bounds[1]; 
        bounds[0].lLbound = 0; 
        bounds[0].cElements = 3; 
        parameters.parray = SafeArrayCreate(VT_VARIANT, 1, bounds); 

        CComVariant varSpeed; 
        varSpeed.vt = VT_R4; 
        varSpeed.fltVal = (float)this->robotSpeed; 

        CComVariant varAcceleration; 
        varAcceleration.vt = VT_R4; 
        varAcceleration.fltVal = (float)(this->robotSpeed*this->robotSpeed/100); 

        CComVariant varDeceleration; 
		varDeceleration.vt = VT_R4; 
        varDeceleration.fltVal = (float)(this->robotSpeed*this->robotSpeed/100); 

		long index = 0; 
        SafeArrayPutElement(parameters.parray, &index, &varSpeed); 
        index = 1; 
		SafeArrayPutElement(parameters.parray, &index, &varAcceleration); 
        index = 2; 
        SafeArrayPutElement(parameters.parray, &index, &varDeceleration); 

        CComVariant vntDummy; 
        hr = pRobot->Execute(CComBSTR(L"ExtSpeed"), parameters, &vntDummy); 
		if(FAILED(hr)) throw exception("Failed to set the external robot speed!");
        parameters.Clear(); 
	}