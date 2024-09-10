// This method receives notification objects.
HRESULT 
WmiSink::Indicate(long lObjectCount, IWbemClassObject** ppObjArray)
{
	// For each object in the array, extract the object and display the
	// information in the object.
	for (long i=0; i<lObjectCount; i++)
	{
		CComVariant vt, vtClass;
		ppObjArray[i]->Get(L"InstanceName", 0, &vt, NULL, NULL);
		ppObjArray[i]->Get(L"__Class", 0, &vtClass, NULL, NULL);

		if (!wcscmp (vtClass.bstrVal, L"MSNdis_StatusMediaDisconnect"))
		{
			if (m_callback) m_callback->onConnectionDown(vt.bstrVal);
		}
		else if (!wcscmp (vtClass.bstrVal, L"MSNdis_StatusMediaConnect"))
		{
			if (m_callback) m_callback->onConnectionUp(vt.bstrVal);
		}
		// notifications we aren't interested in right now:
		//
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_NotifyAdapterRemoval"))
		//{
		//    bstrLog = (_bstr_t) vt.bstrVal;
		//    VariantClear (&vt);
		//    ppObjArray[i]->Get (L"DeviceName", 0, &vt, NULL, NULL);
		//    bstrLog += (_bstr_t) _T(": ") + (_bstr_t) vt.bstrVal + (_bstr_t) _T(" has been removed");
		//    displayDlg.LogEvent (bstrLog);
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_NotifyAdapterArrival"))
		//{
		//    bstrLog = (_bstr_t) vt.bstrVal;
		//    VariantClear (&vt);
		//    ppObjArray[i]->Get(L"DeviceName", 0, &vt, NULL, NULL);
		//    bstrLog += (_bstr_t) _T(": ") + (_bstr_t) vt.bstrVal + (_bstr_t) _T(" has been added");
		//    displayDlg.LogEvent (bstrLog);
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_StatusResetStart"))
		//{
		//    bstrLog = (_bstr_t) vt.bstrVal + (_bstr_t) _T(" has begun a reset");
		//    displayDlg.LogEvent (bstrLog);
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_StatusResetEnd"))
		//{
		//    bstrLog = (_bstr_t) vt.bstrVal + (_bstr_t) _T(" has finished a reset");
		//    displayDlg.LogEvent (bstrLog);
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_NotifyVcArrival"))
		//{
		//    bstrLog = (_bstr_t) _T("VC arrival: ") + (_bstr_t) vt.bstrVal;
		//    displayDlg.LogEvent (bstrLog);
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_NotifyVcRemoval"))
		//{
		//    bstrLog = (_bstr_t) _T("VC removal: ") + (_bstr_t) vt.bstrVal;
		//    displayDlg.LogEvent (bstrLog);
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_StatusMediaSpecificIndication"))
		//{
		//    ATLTRACE (_T("Media specific indication: %s\n"), (TCHAR *) (_bstr_t) vt.bstrVal);
		//    VariantClear (&vt);
		//    ppObjArray[i]->Get (L"NdisStatusMediaSpecificIndication", 0, &vt, NULL, NULL);
		//    LONG lLowerBound, lUpperBound, j;
		//    UCHAR ch;
		//    SafeArrayGetLBound (V_ARRAY (&vt), 1, &lLowerBound);
		//    SafeArrayGetUBound (V_ARRAY (&vt), 1, &lUpperBound);
		//    ATLTRACE (" ");
		//    for (j = lLowerBound; j<= lUpperBound; j++ )
		//    {
		//        SafeArrayGetElement (V_ARRAY (&vt), &j, &ch);
		//        ATLTRACE (_T("%4i"), ch);

		//        if (((j - lLowerBound) % 8 == 7) && (j <= lUpperBound))
		//            ATLTRACE (_T("\n"));         
		//    }                          
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_StatusProtocolBind"))
		//{
		//    bstrLog = (_bstr_t) vt.bstrVal;
		//    VariantClear (&vt);
		//    ppObjArray[i]->Get (L"Transport", 0, &vt, NULL, NULL);
		//    bstrLog += (_bstr_t) _T(" is now bound to ") + (_bstr_t) vt.bstrVal;
		//    displayDlg.LogEvent (bstrLog);
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_StatusProtocolBind"))
		//{
		//    bstrLog = (_bstr_t) vt.bstrVal;
		//    VariantClear (&vt);
		//    ppObjArray[i]->Get(L"Transport", 0, &vt, NULL, NULL);
		//    bstrLog += (_bstr_t) _T(" was unbound from ") + (_bstr_t) vt.bstrVal;
		//    displayDlg.LogEvent (bstrLog);
		//}
		//else if (!wcscmp (vtClass.bstrVal, L"MSNdis_StatusLinkSpeedChange"))
		//{
		//    IWbemClassObject* pWMIObj=NULL;
		//    bstrLog = (_bstr_t) _T("Link speed change ") + (_bstr_t) vt.bstrVal;
		//    VariantClear (&vt);
		//    ppObjArray[i]->Get (L"NdisStatusLinkSpeedChange", 0, &vt, NULL, NULL);
		//    if SUCCEEDED (vt.punkVal->QueryInterface (IID_IWbemClassObject, (void**)&pWMIObj))
		//    {
		//        TCHAR szNum[50];
		//        pWMIObj->Get (L"Inbound", 0, &vt2, NULL, NULL);
		//        _stprintf (szNum, _T(" Inbound = %u "), vt2.lVal);
		//        bstrLog += (_bstr_t) szNum;
		//        VariantClear (&vt2);
		//        pWMIObj->Get (L"Outbound", 0, &vt2, NULL, NULL);
		//        _stprintf (szNum, _T(" Outbound = %u "), vt2.lVal);
		//        bstrLog += (_bstr_t) szNum;
		//        VariantClear (&vt2);
		//        pWMIObj->Release ();
		//        pWMIObj = NULL;
		//    }
		//    displayDlg.LogEvent (bstrLog);
		//}

		VariantClear (&vtClass);
		VariantClear (&vt);
	}
	return WBEM_NO_ERROR;
}