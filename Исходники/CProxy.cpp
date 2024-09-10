/**
* Return the proxy host set by the user.
* @param ctx A Context used to get the settings for the proxy host.
* @return String containing the host name. If the user did not set a host
*         name it returns the default host. A null value means that no
*         host is to be used.
* @deprecated Use standard java vm proxy values to find the host, port
*         and exclusion list.  This call ignores the exclusion list.
*/
ECode CProxy::GetHost(
    /* [in] */ IContext* ctx,
    /* [out] */ String* host)
{
    VALIDATE_NOT_NULL(host);
    AutoPtr<Elastos::Net::IProxy> proxy;
    AutoPtr<Elastos::Net::IProxy> noproxy;
    proxyhelper->GetNO_PROXY((Elastos::Net::IProxy**)&noproxy);
    String str;
    GetProxy(ctx, str, (Elastos::Net::IProxy**)&proxy);
    if (proxy == noproxy) {
        *host = NULL;
        return NOERROR;
    }
    AutoPtr<ISocketAddress> socketAddress;
    proxy->GetAddress((ISocketAddress**)&socketAddress);
    AutoPtr<IInetSocketAddress> address = IInetSocketAddress::Probe(socketAddress);
    return address->GetHostName(host);
}