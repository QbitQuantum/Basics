STDMETHODIMP CLabInput::GetSingleValues(VARIANT* values)
{

    AUTO_LOCK; // Should not be needed inserted on a whim
    if (!_isConfig)
        DAQ_CHECK(Configure(FORSINGLEVALUE));
    // 3 SCANS IS THE MIN with scan_op
    SAFEARRAY *ps = SafeArrayCreateVector(VT_I2, 0, _nChannels*2);
    if (ps==NULL) return E_SAFEARRAY_ERR;

    // set the data type and values
    V_ARRAY(values)=ps;
    V_VT(values)=VT_ARRAY | VT_I2;
    TSafeArrayAccess <short > binarray(values);

    if (_nChannels<=2)
    {
        for (int i=0; i<_nChannels; i++)
        {
            DAQ_CHECK(AI_Read(_id, _chanList[i], _gainList[i], &binarray[i]));
        }
    }
    else
    {
        // setup the channels to read and scan them
        DAQ_TRACE(Set_DAQ_Device_Info(_id, ND_DATA_XFER_MODE_AI, ND_INTERRUPTS));
        short *dummy=(short*)_alloca(_nChannels*sizeof(short));
        DAQ_CHECK(Lab_ISCAN_Op(_id,static_cast<i16>(_nChannels),_gainList[0],&binarray[0],
                               _nChannels, 1.0/_chanSkew,0,dummy));
    }


    return S_OK;
}