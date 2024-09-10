// Create an instance of the Mozilla embeddable browser
//
HRESULT CBrowserView::CreateBrowser()
{
    // Create web shell
    nsresult rv;
    mWebBrowser = do_CreateInstance(NS_WEBBROWSER_CONTRACTID, &rv);
    if(NS_FAILED(rv))
        return rv;

    // Save off the nsIWebNavigation interface pointer
    // in the mWebNav member variable which we'll use
    // later for web page navigation
    //
    rv = NS_OK;
    mWebNav = do_QueryInterface(mWebBrowser, &rv);
    if(NS_FAILED(rv))
        return rv;

//	mSessionHistory = do_GetInterface(mWebBrowser, &rv); // de: added 5/11

    // Create the CBrowserImpl object - this is the object
    // which implements the interfaces which are required
    // by an app embedding mozilla i.e. these are the interfaces
    // thru' which the *embedded* browser communicates with the
    // *embedding* app
    //
    // The CBrowserImpl object will be passed in to the
    // SetContainerWindow() call below
    //
    // Also note that we're passing the BrowserFrameGlue pointer
    // and also the mWebBrowser interface pointer via CBrowserImpl::Init()
    // of CBrowserImpl object.
    // These pointers will be saved by the CBrowserImpl object.
    // The CBrowserImpl object uses the BrowserFrameGlue pointer to
    // call the methods on that interface to update the status/progress bars
    // etc.
    mpBrowserImpl = new CBrowserImpl();
    if(mpBrowserImpl == nsnull)
        return NS_ERROR_OUT_OF_MEMORY;

    // Pass along the mpBrowserFrameGlue pointer to the BrowserImpl object
    // This is the interface thru' which the XP BrowserImpl code communicates
    // with the platform specific code to update status bars etc.
    mpBrowserImpl->Init(mpBrowserFrameGlue, mWebBrowser);
    mpBrowserImpl->AddRef();

    mWebBrowser->SetContainerWindow(static_cast<nsIWebBrowserChrome*>(mpBrowserImpl));

    rv = NS_OK;
    nsCOMPtr<nsIDocShellTreeItem> dsti = do_QueryInterface(mWebBrowser, &rv);
    if(NS_FAILED(rv))
        return rv;
    dsti->SetItemType(nsIDocShellTreeItem::typeContentWrapper);

    // Create the real webbrowser window

    // Note that we're passing the m_hWnd in the call below to InitWindow()
    // (CBrowserView inherits the m_hWnd from CWnd)
    // This m_hWnd will be used as the parent window by the embeddable browser
    //
    rv = NS_OK;
    mBaseWindow = do_QueryInterface(mWebBrowser, &rv);
    if(NS_FAILED(rv))
        return rv;

    // Get the view's ClientRect which to be passed in to the InitWindow()
    // call below
    RECT rcLocation;
    GetClientRect(&rcLocation);
    if(IsRectEmpty(&rcLocation))
    {
        rcLocation.bottom++;
        rcLocation.top++;
    }

    rv = mBaseWindow->InitWindow(nsNativeWidget(m_hWnd), nsnull,
                                 0, 0, rcLocation.right - rcLocation.left, rcLocation.bottom - rcLocation.top);
    rv = mBaseWindow->Create();

    // Register the BrowserImpl object to receive progress messages
    // These callbacks will be used to update the status/progress bars

    /*		// from WinEmbed.cpp
    	nsCOMPtr<nsIWebProgressListener> listener(static_cast<nsIWebProgressListener*>(this));
        nsCOMPtr<nsIWeakReference> thisListener(do_GetWeakReference(listener));
        (void)mWebBrowser->AddWebBrowserListener(thisListener,
           NS_GET_IID(nsIWebProgressListener));

        // The window has been created. Now register for history notifications
        rv = mWebBrowser->AddWebBrowserListener(thisListener, NS_GET_IID(nsISHistoryListener));
    */

    // Finally, show the web browser window
    mBaseWindow->SetVisibility(PR_TRUE);

    qaTests = new CTests(mWebBrowser, mBaseWindow, mWebNav, mpBrowserImpl);
    //nsiRequest = new CNsIRequest(mWebBrowser,mpBrowserImpl);
    return S_OK;
}