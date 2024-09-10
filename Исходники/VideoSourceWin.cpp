/* Extract IIDs and CLSIDs from qedit type library */
static void
InitAllQeditTypeLibGUIDs()
{
    ITypeLib* pQeditTypeLib = 0;
    HRESULT result = LoadTypeLib(
        kFilenameQeditTypeLib.BeginReading(), &pQeditTypeLib
    );
    
    if (result == S_OK) {
        PRUint32 countTypeInfo = pQeditTypeLib->GetTypeInfoCount();
        ITypeInfo** typeInfoPtrArray = new ITypeInfo*[countTypeInfo];
        MEMBERID* memberIdArray = new MEMBERID[countTypeInfo];
        
        InitTypeLibGUID(
            pQeditTypeLib, typeInfoPtrArray, memberIdArray,
            kNameISampleGrabber, TKIND_INTERFACE, IID_ISampleGrabber
        );
        InitTypeLibGUID(
            pQeditTypeLib, typeInfoPtrArray, memberIdArray,
            kNameISampleGrabberCB, TKIND_INTERFACE, IID_ISampleGrabberCB
        );
        InitTypeLibGUID(
            pQeditTypeLib, typeInfoPtrArray, memberIdArray,
            kNameClassSampleGrabber, TKIND_COCLASS, CLSID_SampleGrabber
        );
        InitTypeLibGUID(
            pQeditTypeLib, typeInfoPtrArray, memberIdArray,
            kNameClassNullRenderer, TKIND_COCLASS, CLSID_NullRenderer
        );
        
        delete[] memberIdArray;
        delete[] typeInfoPtrArray;
    }
    
    SAFE_RELEASE(pQeditTypeLib);
}