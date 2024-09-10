STDAPI OleInitializeEx(LPVOID pMalloc, ULONG ulFlags)
{
    OLETRACEIN((API_OleInitialize, PARAMFMT("pMalloc= %p, ulFlags= %x"), pMalloc, ulFlags));
    VDATEHEAP();

    HRESULT hr;
#if DBG==1
    HRESULT hrCoInit = S_OK;
#endif
    DWORD cThreadOleInits;

    StartPerfCounter(CoInitialize);
    hr = CoInitializeEx(pMalloc, ulFlags);
    EndPerfCounter(CoInitialize);

    if (SUCCEEDED(hr))
    {
	Assert (g_hmodOLE2);
#if DBG==1
	hrCoInit = hr;
#endif

	COleTls tls;
	cThreadOleInits = ++ tls->cOleInits;

	do
	{
	    // We only want to do the below initialization once per apartment
	    if (cThreadOleInits > 1)
	    {
		// We've already been this way before, just return
		Assert(SUCCEEDED(hr) && "Bad OleInitializeEx logic");
		break;
	    }

	    // single thread registration of DDE and clipboard formats.
	    // Only do this once per process.

	    COleStaticLock lck(g_mxsSingleThreadOle);

	    if (++g_cOleProcessInits != 1)
	    {
		// already done the per-process initialization
		break;
	    }

	    if (FALSE==DDELibMain (g_hmodOLE2, (WORD)0, (WORD)0, NULL))
	    {
		Assert (!"DDELibMain failed()");

		hr = E_OUTOFMEMORY;
		break;
	    }

	    // Only need to do the initialization once so check the global
	    // that gets assigned last.

	    if( !g_aDropTarget )
	    {
#ifndef _CHICAGO_
	    // on NT3.51, clipboard formats are pre-registered for us by user32.
	    // We know they are going to be sequential.  This gives us a
	    // good performance improvement (since the clipboard formats never
	    // change.

	    // BUGBUG(alexgo); Chicago needs to get this behaviour too

	    g_cfObjectLink = RegisterClipboardFormat(OLESTR("ObjectLink"));

            g_cfOwnerLink = g_cfObjectLink + 1;
	    Assert(g_cfOwnerLink == RegisterClipboardFormat(OLESTR("OwnerLink")));

            g_cfNative = g_cfObjectLink + 2;
            Assert(g_cfNative == RegisterClipboardFormat(OLESTR("Native")));

            g_cfBinary = g_cfObjectLink + 3;
            Assert(g_cfBinary == RegisterClipboardFormat(OLESTR("Binary")));

            g_cfFileName = g_cfObjectLink + 4;
	    Assert(g_cfFileName == RegisterClipboardFormat(OLESTR("FileName")));

            g_cfFileNameW = g_cfObjectLink + 5;
            Assert(g_cfFileNameW ==
                    RegisterClipboardFormat(OLESTR("FileNameW")));

            g_cfNetworkName = g_cfObjectLink + 6;
            Assert(g_cfNetworkName  ==
                    RegisterClipboardFormat(OLESTR("NetworkName")));

            g_cfDataObject = g_cfObjectLink + 7;
            Assert(g_cfDataObject ==
                    RegisterClipboardFormat(OLESTR("DataObject")));

            g_cfEmbeddedObject = g_cfObjectLink + 8;
            Assert(g_cfEmbeddedObject ==
                    RegisterClipboardFormat(OLESTR("Embedded Object")));

            g_cfEmbedSource = g_cfObjectLink + 9;
            Assert(g_cfEmbedSource ==
                    RegisterClipboardFormat(OLESTR("Embed Source")));

            g_cfCustomLinkSource = g_cfObjectLink + 10;
            Assert(g_cfCustomLinkSource  ==
                    RegisterClipboardFormat(OLESTR("Custom Link Source")));

            g_cfLinkSource = g_cfObjectLink + 11;
            Assert(g_cfLinkSource ==
                    RegisterClipboardFormat(OLESTR("Link Source")));

            g_cfObjectDescriptor = g_cfObjectLink + 12;
            Assert(g_cfObjectDescriptor ==
                    RegisterClipboardFormat(OLESTR("Object Descriptor")));

            g_cfLinkSrcDescriptor = g_cfObjectLink + 13;
            Assert(g_cfLinkSrcDescriptor ==
                    RegisterClipboardFormat(OLESTR("Link Source Descriptor")));

            g_cfOleDraw = g_cfObjectLink + 14;
            Assert(g_cfOleDraw == RegisterClipboardFormat(OLESTR("OleDraw")));

            g_cfPBrush = g_cfObjectLink + 15;
            Assert(g_cfPBrush == RegisterClipboardFormat(OLESTR("PBrush")));

            g_cfMSDraw = g_cfObjectLink + 16;
            Assert(g_cfMSDraw == RegisterClipboardFormat(OLESTR("MSDraw")));

            g_cfOlePrivateData = g_cfObjectLink + 17;
            Assert(g_cfOlePrivateData ==
                    RegisterClipboardFormat(OLESTR("Ole Private Data")));

            g_cfScreenPicture = g_cfObjectLink + 18;
            Assert(g_cfScreenPicture  ==
                RegisterClipboardFormat(OLESTR("Screen Picture")));

            g_aDropTarget = GlobalAddAtom(OLE_DROP_TARGET_PROP);
            AssertSz(g_aDropTarget, "Couldn't add drop target atom\n");
	    }

	    // Used in Inplace editing
	    uOmPostWmCommand = RegisterWindowMessage(OLESTR("OM_POST_WM_COMMAND"));
	    uOleMessage	     = RegisterWindowMessage(OLESTR("OLE_MESSAHE"));

#else  //  !_CHICAGO_

	    g_cfObjectLink	  = SSRegisterClipboardFormatA("ObjectLink");
            g_cfOwnerLink         = SSRegisterClipboardFormatA("OwnerLink");
            g_cfNative            = SSRegisterClipboardFormatA("Native");
            g_cfBinary            = SSRegisterClipboardFormatA("Binary");
            g_cfFileName          = SSRegisterClipboardFormatA("FileName");
            g_cfFileNameW         = SSRegisterClipboardFormatA("FileNameW");
            g_cfNetworkName       = SSRegisterClipboardFormatA("NetworkName");
            g_cfDataObject        = SSRegisterClipboardFormatA("DataObject");
            g_cfEmbeddedObject    = SSRegisterClipboardFormatA("Embedded Object");
            g_cfEmbedSource       = SSRegisterClipboardFormatA("Embed Source");
            g_cfCustomLinkSource  = SSRegisterClipboardFormatA("Custom Link Source");
            g_cfLinkSource        = SSRegisterClipboardFormatA("Link Source");
            g_cfObjectDescriptor  = SSRegisterClipboardFormatA("Object Descriptor");
            g_cfLinkSrcDescriptor = SSRegisterClipboardFormatA("Link Source Descriptor");
            g_cfOleDraw           = SSRegisterClipboardFormatA("OleDraw");
            g_cfPBrush            = SSRegisterClipboardFormatA("PBrush");
            g_cfMSDraw            = SSRegisterClipboardFormatA("MSDraw");
            g_cfOlePrivateData    = SSRegisterClipboardFormatA("Ole Private Data");
            g_cfScreenPicture     = SSRegisterClipboardFormatA("Screen Picture");
            g_aDropTarget         = GlobalAddAtomA(OLE_DROP_TARGET_PROPA);
            AssertSz(g_aDropTarget, "Couldn't add drop target atom\n");
	    }

	    // Used in Inplace editing
	    uOmPostWmCommand = RegisterWindowMessageA("OM_POST_WM_COMMAND");
	    uOleMessage	     = RegisterWindowMessageA("OLE_MESSAHE");

#endif // !_CHICAGO_

	} while (FALSE); // end of do


	if (FAILED(hr))
	{
	    // clean up and break out
	    DDEWEP (WEP_FREE_DLL);

	    tls->cOleInits--;
	    CoUninitialize();
	}
	else
	{
#if defined(_CHICAGO_)
	    if (!gfShellInitialized && CoGetCurrentProcess() == 1)
	    {
		//  The Chicago Shell will dynamically load the OLE32.DLL to improve
		//  bootup start time.	    When an application calls CoInitialize, post
		//  a message to the shell to inform it to load OLE32.DLL if it hasn't
		//  already.   The Shell will never unload OLE32.DLL.
		//
		//  We are using an undocumented Shell interface.
		//
		//  We do this last so that we dont take a task switch while in
		//  CoInitialize.
#if DBG==1
		if (RegQueryValueEx(HKEY_CURRENT_USER,
                            L"Software\\Microsoft\\OLE2\\NoShellNotify",
                            NULL,  // reserved
                            NULL,  // lpdwType
                            NULL,  // lpbData
                            NULL) != ERROR_SUCCESS) // lpcbData
#endif
		{
		    HWND hwndShell = GetShellWindow();
		    if (hwndShell)
		    {
			PostMessage(hwndShell,WM_SHELLNOTIFY,
                                 SHELLNOTIFY_OLELOADED,0L);
		    }
		}

	    }

	    gfShellInitialized = TRUE;
#endif  // _CHICAGO_

	    Assert(SUCCEEDED(hr) && "Bad OleInitializeEx logic");

	    //	If we're overriding the allocator, we return whatever
	    //	CoInitializeEx returned

	    if (NULL != pMalloc)
	    {
		Assert(hr == hrCoInit && "Bad OleInit logic");
	    }
	    else if (1 == cThreadOleInits)
	    {
		//  First successful call to OleInitializeEx - S_OK
		hr = S_OK;
	    }
	    else
	    {
		//  Second or greater succesful call to OleInitializeEx - S_FALSE
		hr = S_FALSE;
	    }
	}
    }