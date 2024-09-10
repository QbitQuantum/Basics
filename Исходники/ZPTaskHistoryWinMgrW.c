long EmbedBrowserObject(HWND hwnd)
{
	LPCLASSFACTORY		pClassFactory;
	IOleObject			*browserObject;
	IWebBrowser2		*webBrowser2;
	RECT				rect;
	char				*ptr;
	_IOleClientSiteEx	*_iOleClientSiteEx;

	// Our IOleClientSite, IOleInPlaceSite, and IOleInPlaceFrame functions need to get our window handle. We
	// could store that in some global. But then, that would mean that our functions would work with only that
	// one window. If we want to create multiple windows, each hosting its own browser object (to display its
	// own web page), then we need to create unique IOleClientSite, IOleInPlaceSite, and IOleInPlaceFrame
	// structs for each window. And we'll put an extra field at the end of those structs to store our extra
	// data such as a window handle. So, our functions won't have to touch global data, and can therefore be
	// re-entrant and work with multiple objects/windows.
	//
	// Remember that a pointer to our IOleClientSite we create here will be passed as the first arg to every
	// one of our IOleClientSite functions. Ditto with the IOleInPlaceFrame object we create here, and the
	// IOleInPlaceFrame functions. So, our functions are able to retrieve the window handle we'll store here,
	// and then, they'll work with all such windows containing a browser control.
	//
	// Furthermore, since the browser will be calling our IOleClientSite's QueryInterface to get a pointer to
	// our IOleInPlaceSite and IDocHostUIHandler objects, that means that our IOleClientSite QueryInterface
	// must have an easy way to grab those pointers. Probably the easiest thing to do is just embed our
	// IOleInPlaceSite and IDocHostUIHandler objects inside of an extended IOleClientSite which we'll call
	// a _IOleClientSiteEx. As long as they come after the pointer to the IOleClientSite VTable, then we're
	// ok.
	//
	// Of course, we need to GlobalAlloc the above structs now. We'll just get all 4 with a single call to
	// GlobalAlloc, especially since 3 of them are all contained inside of our _IOleClientSiteEx anyway.
	//
	// So, we're not actually allocating separate IOleClientSite, IOleInPlaceSite, IOleInPlaceFrame and
	// IDocHostUIHandler structs.
	//
	// One final thing. We're going to allocate extra room to store the pointer to the browser object.
	if (!(ptr = (char *)GlobalAlloc(GMEM_FIXED, sizeof(_IOleClientSiteEx) + sizeof(IOleObject *))))
		return(-1);

	// Initialize our IOleClientSite object with a pointer to our IOleClientSite VTable.
	_iOleClientSiteEx = (_IOleClientSiteEx *)(ptr + sizeof(IOleObject *));
	_iOleClientSiteEx->client.lpVtbl = &gIOleClientSiteTable;

	// Initialize our IOleInPlaceSite object with a pointer to our IOleInPlaceSite VTable.
	_iOleClientSiteEx->inplace.inplace.lpVtbl = &gIOleInPlaceSiteTable;

	// Initialize our IOleInPlaceFrame object with a pointer to our IOleInPlaceFrame VTable.
	_iOleClientSiteEx->inplace.frame.frame.lpVtbl = &gIOleInPlaceFrameTable;

	// Save our HWND (in the IOleInPlaceFrame object) so our IOleInPlaceFrame functions can retrieve it.
	_iOleClientSiteEx->inplace.frame.window = hwnd;

	// Initialize our IDocHostUIHandler object with a pointer to our IDocHostUIHandler VTable.
	_iOleClientSiteEx->ui.ui.lpVtbl = &gIDocHostUIHandlerTable;

	// Get a pointer to the browser object and lock it down (so it doesn't "disappear" while we're using
	// it in this program). We do this by calling the OS function CoGetClassObject().
	//	
	// NOTE: We need this pointer to interact with and control the browser. With normal WIN32 controls such as a
	// Static, Edit, Combobox, etc, you obtain an HWND and send messages to it with SendMessage(). Not so with
	// the browser object. You need to get a pointer to its "base structure" (as returned by CoGetClassObject()). This
	// structure contains an array of pointers to functions you can call within the browser object. Actually, the
	// base structure contains a 'lpVtbl' field that is a pointer to that array. We'll call the array a 'VTable'.
	//
	// For example, the browser object happens to have a SetHostNames() function we want to call. So, after we
	// retrieve the pointer to the browser object (in a local we'll name 'browserObject'), then we can call that
	// function, and pass it args, as so:
	//
	// browserObject->lpVtbl->SetHostNames(browserObject, SomeString, SomeString);
	//
	// There's our pointer to the browser object in 'browserObject'. And there's the pointer to the browser object's
	// VTable in 'browserObject->lpVtbl'. And the pointer to the SetHostNames function happens to be stored in an
	// field named 'SetHostNames' within the VTable. So we are actually indirectly calling SetHostNames by using
	// a pointer to it. That's how you use a VTable.
	//
	// NOTE: We pass our _IOleClientSiteEx struct and lie -- saying that it's a IOleClientSite. It's ok. A
	// _IOleClientSiteEx struct starts with an embedded IOleClientSite. So the browser won't care, and we want
	// this extended struct passed to our IOleClientSite functions.

	// Get a pointer to the browser object's IClassFactory object via CoGetClassObject()
	pClassFactory = 0;
	if (!CoGetClassObject(&CLSID_WebBrowser, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER, NULL, &IID_IClassFactory, (void **)&pClassFactory) && pClassFactory)
	{
		// Call the IClassFactory's CreateInstance() to create a browser object
		if (!pClassFactory->lpVtbl->CreateInstance(pClassFactory, 0, &IID_IOleObject, &browserObject))
		{
			// Free the IClassFactory. We need it only to create a browser object instance
			pClassFactory->lpVtbl->Release(pClassFactory);

			// Ok, we now have the pointer to the browser object in 'browserObject'. Let's save this in the
			// memory block we allocated above, and then save the pointer to that whole thing in our window's
			// USERDATA field. That way, if we need multiple windows each hosting its own browser object, we can
			// call EmbedBrowserObject() for each one, and easily associate the appropriate browser object with
			// its matching window and its own objects containing per-window data.
			*((IOleObject **)ptr) = browserObject;
			SetWindowLong(hwnd, GWL_USERDATA, (LONG)ptr);

			// Give the browser a pointer to my IOleClientSite object
			if (!browserObject->lpVtbl->SetClientSite(browserObject, (IOleClientSite *)_iOleClientSiteEx))
			{
				// We can now call the browser object's SetHostNames function. SetHostNames lets the browser object know our
				// application's name and the name of the document in which we're embedding the browser. (Since we have no
				// document name, we'll pass a 0 for the latter). When the browser object is opened for editing, it displays
				// these names in its titlebar.
				//	
				// We are passing 3 args to SetHostNames. You'll note that the first arg to SetHostNames is the base
				// address of our browser control. This is something that you always have to remember when working in C
				// (as opposed to C++). When calling a VTable function, the first arg to that function must always be the
				// structure which contains the VTable. (In this case, that's the browser control itself). Why? That's
				// because that function is always assumed to be written in C++. And the first argument to any C++ function
				// must be its 'this' pointer (ie, the base address of its class, which in this case is our browser object
				// pointer). In C++, you don't have to pass this first arg, because the C++ compiler is smart enough to
				// produce an executable that always adds this first arg. In fact, the C++ compiler is smart enough to
				// know to fetch the function pointer from the VTable, so you don't even need to reference that. In other
				// words, the C++ equivalent code would be:
				//
				// browserObject->SetHostNames(L"My Host Name", 0);
				//
				// So, when you're trying to convert C++ code to C, always remember to add this first arg whenever you're
				// dealing with a VTable (ie, the field is usually named 'lpVtbl') in the standard objects, and also add
				// the reference to the VTable itself.
				//
				// Oh yeah, the L is because we need UNICODE strings. And BTW, the host and document names can be anything
				// you want.
				browserObject->lpVtbl->SetHostNames(browserObject, L"My Host Name", 0);

				GetClientRect(hwnd, &rect);

				// Let browser object know that it is embedded in an OLE container.
				if (!OleSetContainedObject((struct IUnknown *)browserObject, TRUE) &&

					// Set the display area of our browser control the same as our window's size
					// and actually put the browser object into our window.
					!browserObject->lpVtbl->DoVerb(browserObject, OLEIVERB_SHOW, NULL, (IOleClientSite *)_iOleClientSiteEx, -1, hwnd, &rect) &&

					// Ok, now things may seem to get even trickier, One of those function pointers in the browser's VTable is
					// to the QueryInterface() function. What does this function do? It lets us grab the base address of any
					// other object that may be embedded within the browser object. And this other object has its own VTable
					// containing pointers to more functions we can call for that object.
					//
					// We want to get the base address (ie, a pointer) to the IWebBrowser2 object embedded within the browser
					// object, so we can call some of the functions in the former's table. For example, one IWebBrowser2 function
					// we intend to call below will be Navigate2(). So we call the browser object's QueryInterface to get our
					// pointer to the IWebBrowser2 object.
					!browserObject->lpVtbl->QueryInterface(browserObject, &IID_IWebBrowser2, (void**)&webBrowser2))
				{
					// Ok, now the pointer to our IWebBrowser2 object is in 'webBrowser2', and so its VTable is
					// webBrowser2->lpVtbl.

					// Let's call several functions in the IWebBrowser2 object to position the browser display area
					// in our window. The functions we call are put_Left(), put_Top(), put_Width(), and put_Height().
					// Note that we reference the IWebBrowser2 object's VTable to get pointers to those functions. And
					// also note that the first arg we pass to each is the pointer to the IWebBrowser2 object.
					webBrowser2->lpVtbl->put_Left(webBrowser2, 0);
					webBrowser2->lpVtbl->put_Top(webBrowser2, 0);
					webBrowser2->lpVtbl->put_Width(webBrowser2, rect.right);
					webBrowser2->lpVtbl->put_Height(webBrowser2, rect.bottom);

					// We no longer need the IWebBrowser2 object (ie, we don't plan to call any more functions in it
					// right now, so we can release our hold on it). Note that we'll still maintain our hold on the
					// browser object until we're done with that object.
					webBrowser2->lpVtbl->Release(webBrowser2);

					// Success
					return(0);
				}
			}

			// Something went wrong setting up the browser!
			UnEmbedBrowserObject(hwnd);
			return(-4);
		}

		pClassFactory->lpVtbl->Release(pClassFactory);
		GlobalFree(ptr);

		// Can't create an instance of the browser!
		return(-3);
	}

	GlobalFree(ptr);

	// Can't get the web browser's IClassFactory!
	return(-2);
}