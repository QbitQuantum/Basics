HRESULT CTestMessageHandler::ValidateMappedAddress(CStunMessageReader& reader, const CSocketAddress& addrClient)
{
    HRESULT hr = S_OK;
    StunTransactionId transid;
    CSocketAddress mappedaddr;
    
    CRefCountedBuffer spBuffer;
    
    Chk(reader.GetStream().GetBuffer(&spBuffer));
    
    reader.GetTransactionId(&transid);

    //ChkA(reader.GetAttributeByType(STUN_ATTRIBUTE_XORMAPPEDADDRESS, &attrib));
    //ChkA(GetXorMappedAddress(spBuffer->GetData()+attrib.offset, attrib.size, transid, &mappedaddr));
    reader.GetXorMappedAddress(&mappedaddr);
    ChkIfA(false == addrClient.IsSameIP_and_Port(mappedaddr), E_FAIL);    
    
    //ChkA(reader.GetAttributeByType(STUN_ATTRIBUTE_MAPPEDADDRESS, &attrib));
    //ChkA(GetMappedAddress(spBuffer->GetData()+attrib.offset, attrib.size, &mappedaddr));
    
    reader.GetMappedAddress(&mappedaddr);
    ChkIfA(false == addrClient.IsSameIP_and_Port(mappedaddr), E_FAIL);    
    
Cleanup:
    return hr;
}