/// Function name  : DAdvise
// Description     : Register for a 'data changed' notification
// 
// FORMATETC*    pFormat          : [in]  The data format to monitor for changes
// DWORD         dwFlags          : [in]  flags
// IAdviseSink*  pOutput          : [out] The OLE object to call when changes occurr
// DWORD*        pdwConnectionID  : [out] Unique ID to identify the event
// 
// Return Value   : S_OK if succesful
// 
OLE_Method
HRESULT  RichEditImage::DAdvise(FORMATETC*  pFormat, DWORD  dwFlags, IAdviseSink*  pOutput, DWORD*  pdwConnectionID)
{
   HRESULT  hResult;    // Operation result

   // Create events object if necessary
   if (!m_pEvents AND FAILED(hResult = CreateDataAdviseHolder(&m_pEvents)))
      return hResult;

   // Register connect using events object
   return m_pEvents->Advise(this, pFormat, dwFlags, pOutput, pdwConnectionID);
}