NS_IMETHODIMP 
CWebBrowserContainer::OnStatusChange(nsIWebProgress* aWebProgress,
                                     nsIRequest* aRequest,
                                     nsresult aStatus,
                                     const PRUnichar* aMessage)
{
    NG_TRACE(_T("CWebBrowserContainer::OnStatusChange(...,  \"\")\n"));

    BSTR bstrStatus = SysAllocString(W2OLE((PRUnichar *) aMessage));
    mEvents1->Fire_StatusTextChange(bstrStatus);
    mEvents2->Fire_StatusTextChange(bstrStatus);
    SysFreeString(bstrStatus);

    return NS_OK;
}