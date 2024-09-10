ECode InetAddress::LookupHostByName(
    /* [in] */ const String& host,
    /* [in] */ Int32 netId,
    /* [out, callee] */ ArrayOf<IInetAddress*>** addresses)
{
    VALIDATE_NOT_NULL(addresses);
    *addresses = NULL;

    AutoPtr<IBlockGuardPolicy> policy;
    BlockGuard::GetThreadPolicy((IBlockGuardPolicy**)&policy);
    policy->OnNetwork();

    // Do we have a result cached?
    AutoPtr<AddressCacheEntry> cachedResult = ADDRESS_CACHE->Get(host, netId);
    if (cachedResult != NULL) {
        if (cachedResult->mValue != NULL) {
            *addresses = cachedResult->mValue;
            REFCOUNT_ADD(*addresses);
            return NOERROR;
        }
        else {
            // A cached negative result.
            // throw new UnknownHostException((String) cachedResult);
            return E_UNKNOWN_HOST_EXCEPTION;
        }
    }

    AutoPtr<ArrayOf<IInetAddress*> > structAddresses;
    AutoPtr<IStructAddrinfo> hints;
    ECode ec = CStructAddrinfo::New((IStructAddrinfo**)&hints);
    FAIL_GOTO(ec, _EXIT_)

    hints->SetFlags(AI_ADDRCONFIG);
    hints->SetFamily(AF_UNSPEC);
    // If we don't specify a socket type, every address will appear twice, once
    // for SOCK_STREAM and one for SOCK_DGRAM. Since we do not return the family
    // anyway, just pick one.
    hints->SetSocktype(SOCK_STREAM);

    ec = CLibcore::sOs->Elastos_getaddrinfo(host, hints, netId, (ArrayOf<IInetAddress*>**)&structAddresses);
    FAIL_GOTO(ec, _EXIT_)

    if (structAddresses != NULL) {
        // TODO: should getaddrinfo set the hostname of the InetAddresses it returns?
        for (Int32 i = 0; i < structAddresses->GetLength(); i++) {
            InetAddress* inetAddressObj = (InetAddress*)(*structAddresses)[i];
            inetAddressObj->mHostname = host;
        }
    }

    ADDRESS_CACHE->Put(host, netId, structAddresses);
    *addresses = structAddresses;
    REFCOUNT_ADD(*addresses);
    return NOERROR;

_EXIT_:
    if ((ECode)E_GAI_EXCEPTION == ec) {
        ADDRESS_CACHE->PutUnknownHost(host, netId, String("Unable to resolve") + host);
        ec = E_UNKNOWN_HOST_EXCEPTION;
    }
    return ec;
}