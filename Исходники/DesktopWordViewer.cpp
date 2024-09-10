Error WordViewer::showDocument(QString& path)
{
   Error errorHR = Success();
   HRESULT hr = S_OK;

   // Allow Word to become the foreground window. CoAllowSetForegroundWindow
   // would be preferable here, since we'd be able to restrict activation to
   // only the process we started, but it is not exposed by MinGW headers.
   // Note that AllowSetForegroundWindow already limits activation to processes
   // initiated by the foreground process, and self-expires on user input.
   AllowSetForegroundWindow(ASFW_ANY);

   // If we have an active IDispatch pointer to Word, check to see whether
   // it has been closed
   if (idispWord_ != NULL)
   {
      // Test the interface by looking up a known DISPID
      const WCHAR* wstrQuit = L"Quit";
      DISPID dispid;
      hr = idispWord_->GetIDsOfNames(IID_NULL, const_cast<WCHAR**>(&wstrQuit),
                                     1, LOCALE_USER_DEFAULT, &dispid);

      // If the lookup fails, release this IDispatch pointer--it's stale.
      // We'll CoCreate a new instance of Word below.
      if (FAILED(hr) &&
          SCODE_CODE(hr) == RPC_S_SERVER_UNAVAILABLE)
      {
         idispWord_->Release();
         idispWord_ = NULL;
      }
   }

   // Get an IDispatch for the Word Application root object
   if (idispWord_ == NULL)
   {
      CLSID clsid;
      LPCOLESTR progId = L"Word.Application";
      CoInitialize(NULL);
      VERIFY_HRESULT(CLSIDFromProgID(progId, &clsid));
      VERIFY_HRESULT(CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER,
                                      IID_IDispatch,
                                      reinterpret_cast<void**>(&idispWord_)));
      idispWord_->AddRef();
   }

   // Make Word visible
   errorHR = showWord();
   if (errorHR)
      return errorHR;

   IDispatch* idispDocs;
   IDispatch* idispDoc;
   VERIFY_HRESULT(getIDispatchProp(idispWord_, L"Documents", &idispDocs));

   // Open the documenet
   path = path.replace(QChar(L'/'), QChar(L'\\'));
   errorHR = openDocument(path, idispDocs, &idispDoc);
   if (errorHR)
      return errorHR;
   if (docPath_ == path)
   {
      // Reopening the last-opened doc: apply the scroll position if we have
      // one cached
      if (docScrollX_ > 0 || docScrollY_ > 0)
         setDocumentPosition(idispDoc, docScrollX_, docScrollY_);
   }
   else
   {
      // Opening a different doc: forget scroll position and save the doc name
      docScrollX_ = 0;
      docScrollY_ = 0;
      docPath_ = path;
   }

   // Bring Word to the foreground
   VERIFY_HRESULT(invokeDispatch(DISPATCH_METHOD, NULL, idispWord_,
                                 L"Activate", 0));

LErrExit:
   return errorHR;
}