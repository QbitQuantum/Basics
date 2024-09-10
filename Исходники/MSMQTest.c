//-----------------------------------------------------
//
// Check whether the local computer is enabled to access
// the directory service (DS-enabled).
//
//----------------------------------------------------- 
int DetectDsConnection(void)
{

    MQPRIVATEPROPS PrivateProps;
    QMPROPID       aPropId[MAX_VAR];
    MQPROPVARIANT  aPropVar[MAX_VAR];
    HRESULT        aStatus[MAX_VAR];

    DWORD          cProp;
    
    HRESULT        hr;


    //
    // Specify the PROPID_PC_DS_ENABLED property, which
	// indicates whether the local computer can access the DS.
    //
    cProp = 0;

    aPropId[cProp] = PROPID_PC_DS_ENABLED;
    aPropVar[cProp].vt = VT_NULL;
    ++cProp;	

    // Create a PRIVATEPROPS structure.
    PrivateProps.cProp = cProp;
	PrivateProps.aPropID = aPropId;
	PrivateProps.aPropVar = aPropVar;
    PrivateProps.aStatus = aStatus;
    //
    // Retrieve the information.
    //
	hr = MQGetPrivateComputerInformation(
				     NULL,
					 &PrivateProps);
	if(FAILED(hr))
	{
        Error("A DS connection cannot be detected", hr);
    }
	
    
    if(PrivateProps.aPropVar[0].boolVal == 0)
        return DS_DISABLED;
    

    return DS_ENABLED;
}