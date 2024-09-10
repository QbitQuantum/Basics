void CMSDNForumHelper::RevealHiddenLinks(IHTMLDocument2* pDocument)
{
	CComBSTR url;
	HRESULT hr=pDocument->get_URL(&url);
	if(hr==S_OK)
	{
		url.ToLower();
		CString urlString(url);
		if(urlString.Find(_T("microsoft.com"))==-1)
			return;
		if(urlString.Find(_T("social"))==1)
			return;
		
	}
    CComPtr<IHTMLElementCollection> linkElementCollection;

    // Get the collection of images from the DOM.
	 hr = pDocument->get_links(&linkElementCollection);
    if (hr == S_OK && linkElementCollection != NULL)
    {
        // Get the number of images in the collection.
        long linkCount = 0;
        hr = linkElementCollection->get_length(&linkCount);
        if (hr == S_OK && linkCount > 0)
        {
            for (int i = 0; i < linkCount; i++)
            {
                CComVariant varItemIndex(i);
                CComVariant varEmpty;
                CComPtr<IDispatch> linkDispatch;
                // Get the link out of the collection by index.
                hr = linkElementCollection->item(varItemIndex, varEmpty, &linkDispatch);
                if (hr == S_OK && linkDispatch != NULL)
                {
					//filter out hot spot on images
					CComQIPtr<IHTMLAnchorElement> anchorElement(linkDispatch);
					if(anchorElement==NULL) continue;
                    //query for the generic HTML element interface
					CComQIPtr<IHTMLElement> linkElement(linkDispatch);					
                    if (linkElement)
                    {
                        // ...then ask for the style interface.
                        CComPtr<IHTMLStyle> linkStyle;
						hr = linkElement->get_style(&linkStyle);

                        // Set display="none" to hide the image.
                        if (hr == S_OK && linkStyle != NULL)
                        {                            
							CComVariant linkCollor;
							hr=linkStyle->get_color(&linkCollor);
							if(linkCollor.vt==VT_BSTR)
							{
								CComBSTR linkCollorString(linkCollor.bstrVal);
								if (hr == S_OK && linkCollorString.Length()>0)
								{
									linkStyle->put_backgroundColor(CComVariant(_T("red")));
									linkStyle->put_color(CComVariant(_T("")));
									CComBSTR href,text;
									anchorElement->get_href(&href);
									linkElement->get_innerText(&text);
									CString newText;
									newText.Format(_T("hidden link, possible spam: text: %s, url: %s"),text,href);
									linkElement->put_innerText(CComBSTR(newText));
								}
							}
                        }
                    }
                }
            }
        }
    }
}