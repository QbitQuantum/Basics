/*
Modify this to avoid temp file I/O
*/
bool CXMLParser::extractData( wstring filename)
{
    bool bRet = false;
    HRESULT hr = S_OK;
    IXmlReader *pReader = nullptr;
    IStream *pStream = nullptr;
    XmlNodeType nodeType;
    const TCHAR* pwszName;
    const TCHAR* pwszValue;

    if (FAILED(hr = SHCreateStreamOnFile(filename.c_str(), STGM_READ, &pStream)))
    {
        return bRet;
    }
    if (!GetDataContainer())
    {
        if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**)&pReader, nullptr)))
        {
            return bRet;
        }
        if (FAILED(hr = pReader->SetInput(pStream)))
        {
            return bRet;
        }
        bool inKey = false;
        wstring csKeyFoundStr;
        while (!pReader->IsEOF())
        {
            pReader->Read(&nodeType);
            switch (nodeType)
            {
            case XmlNodeType_Element:
                if (S_OK == pReader->GetLocalName(&pwszName, nullptr))
                {
                    if (true == isNodeInKeys(pwszName))
                    {
                        inKey = true;
                        csKeyFoundStr = pwszName;
                    }
                }
                break;
            case XmlNodeType_CDATA:
            case XmlNodeType_Text:
            {
                if (true == inKey)
                {
                    if (S_OK == pReader->GetValue(&pwszValue, nullptr))
                    {
                        GetDataContainer()->setkeyValue(csKeyFoundStr, pwszValue);
                        inKey = false;
                        bRet = true;
                    }
                }
            }
            break;
            default:
                break;
            }
        }
    }
    return bRet;
}