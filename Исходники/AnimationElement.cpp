Element* ElementAnimation::get_targetElement()
{
	return m_targetElement;
#if 0
// Try targetElement attribute
	CComBSTR targetElement;
	static_cast<T*>(this)->getAttribute(L"targetElement", &targetElement);
	if (targetElement.Length() > 0)
	{
		static_cast<T*>(this)->m_ownerDocument->getElementById(targetElement, pVal);
		if (*pVal) return S_OK;
	}

// Try href:xlink attribute
	CComBSTR href;
	static_cast<T*>(this)->getAttributeNS(WSTR("http://www.w3.org/1999/xlink"), WSTR("href"), &href);
	if (href.Length())
	{
		if (((BSTR)href)[0] == L'#')
		{
			BSTR id = &((BSTR)href)[1];
			static_cast<T*>(this)->m_ownerDocument->getElementById(id, pVal);
			if (*pVal) return S_OK;
		}
	}

// Try parent element
	CComPtr<ILDOMNode> parentNode;
	static_cast<T*>(this)->get_parentNode(&parentNode);

	CComQIPtr<Element, &IID_Element> parentElement((IUnknown*)parentNode);
	*pVal = parentElement.Detach();
	return NULL;
#endif
}