/**
 *  Erstellt per UPnP ein Portforwarding.
 *
 *  @author FloSoft
 */
bool UPnP::OpenPort(const unsigned short& port)
{
    if(remote_port_ != 0)
        ClosePort();

    remote_port_ = port;

#ifdef _MSC_VER
    HRESULT hr;

    CoInitialize(NULL);

    IUPnPNAT* upnpnat;
    hr = CoCreateInstance (CLSID_UPnPNAT, NULL, CLSCTX_INPROC_SERVER, IID_IUPnPNAT, (void**)&upnpnat);
    if(FAILED(hr) || !upnpnat)
    {
        if(!upnpnat)
            hr = E_NOINTERFACE;
        SetLastError(hr);
        return false;
    }

    IStaticPortMappingCollection* upnpspmc = NULL;
    hr = upnpnat->get_StaticPortMappingCollection(&upnpspmc);
    if(FAILED(hr) || !upnpspmc)
    {
        if(!upnpspmc)
            hr = E_NOINTERFACE;
        SetLastError(hr);
        return false;
    }

    std::string local_address;
    std::vector<std::string> addresses = GetAllv4Addresses();

    // if we have multiple addresses, search the private one
    if(addresses.size() > 1)
    {
        for(std::vector<std::string>::iterator addr = addresses.begin(); addr != addresses.end(); ++addr)
        {
            std::string ss = *addr;
            std::stringstream s, sc;
            s << ss;
            std::getline(s, ss, '.');
            sc << ss << " ";
            std::getline(s, ss, '.');
            sc << ss << " ";

            int a, b;
            sc >> a;
            sc >> b;

            int ab = (a << 24) | (b << 16);

            if( (ab & 0xff000000) == 0x0a000000 || // 10.0.0.0/8
                    (ab & 0xff000000) == 0x7f000000 || // 127.0.0.0/8
                    (ab & 0xfff00000) == 0xac100000 || // 172.16.0.0/12
                    (ab & 0xffff0000) == 0xc0a80000 )  // 192.168.0.0/16
                local_address = *addr;
        }
    }

    // otherwise use the first one
    if(local_address == "" && !addresses.empty())
        local_address = addresses.front();

    // I hope we found one ...
    if(local_address == "")
    {
        SetLastError(E_FAIL);
        return false;
    }

    BSTR bstrProtocol = A2BSTR("TCP");
    BSTR bstrLocalAddress = A2BSTR(local_address.c_str());
    BSTR bstrDescription = A2BSTR("Return To The Roots");

    IStaticPortMapping* upnpspm = NULL;
    hr = upnpspmc->Add(port, bstrProtocol, port, bstrLocalAddress, VARIANT_TRUE, bstrDescription, &upnpspm);

    SysFreeString(bstrProtocol);
    SysFreeString(bstrLocalAddress);
    SysFreeString(bstrDescription);

    if(SUCCEEDED(hr) && !upnpspm)
        hr = E_NOINTERFACE;

    SetLastError(hr);

    if(SUCCEEDED(hr) && upnpspm)
        return true;
#else
    int hr;
    UPNPDev* devicelist = NULL;
#ifdef UPNPDISCOVER_SUCCESS
    int upnperror = 0;
    devicelist = upnpDiscover(2000, NULL, NULL, 0, 0 /* ipv6 */, &upnperror);
#else
    devicelist = upnpDiscover(2000, NULL, NULL, 0);
#endif
    if(!devicelist)
        return false;

    UPNPUrls urls;
    IGDdatas data;
    char lanAddr[64];
    hr = UPNP_GetValidIGD(devicelist, &urls, &data, lanAddr, sizeof(lanAddr));

    if(hr == 1 || hr == 2)
    {
        std::stringstream p;
        p << port;

#ifdef UPNPDISCOVER_SUCCESS
        hr = UPNP_AddPortMapping(urls.controlURL, data.first.servicetype, p.str().c_str(), p.str().c_str(), lanAddr, "Return To The Roots", "TCP", NULL, NULL);
#else
        hr = UPNP_AddPortMapping(urls.controlURL, data.first.servicetype, p.str().c_str(), p.str().c_str(), lanAddr, "Return To The Roots", "TCP", NULL);
#endif
    }

    freeUPNPDevlist(devicelist);

    if(hr == 0)
        return true;
#endif
    return false;
}