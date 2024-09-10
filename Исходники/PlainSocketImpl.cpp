AutoPtr<IInetAddress> PlainSocketImpl::SocksGetServerAddress()
{
    String proxyName;
    // get socks server address from proxy. It is unnecessary to check
    // "socksProxyHost" property, since all proxy setting should be
    // determined by ProxySelector.
    AutoPtr<IInetSocketAddress> addr;
    mProxy->GetAddress((ISocketAddress**)&addr);
    addr->GetHostName(&proxyName);
    if (proxyName.IsNull()) {
        AutoPtr<IInetAddress> iaddr;
        addr->GetAddress((IInetAddress**)&iaddr);
        iaddr->GetHostAddress(&proxyName);
    }

    AutoPtr<IInetAddressHelper> helper;
    CInetAddressHelper::AcquireSingleton((IInetAddressHelper**)&helper);
    AutoPtr<IInetAddress> retAddr;
    helper->GetByName(proxyName, (IInetAddress**)&retAddr);
    return retAddr;
}