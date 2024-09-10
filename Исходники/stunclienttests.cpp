HRESULT CStunClientTestBase::BasicReaderValidation(CRefCountedBuffer& spMsg, CStunMessageReader& reader)
{
    HRESULT hr = S_OK;
    CStunMessageReader::ReaderParseState readerstate;
    StunTransactionId transid;
    int cmp = 0;

    readerstate = reader.AddBytes(spMsg->GetData(), spMsg->GetSize());
    ChkIf(readerstate != CStunMessageReader::BodyValidated, E_FAIL);

    reader.GetTransactionId(&transid);

    cmp = memcmp(transid.id, _transid.id, sizeof(_transid));

    ChkIf(cmp!=0, E_FAIL);

Cleanup:
    return hr;
}