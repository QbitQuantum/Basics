HRESULT CTestClientLogic::ValidateBindingRequest(CRefCountedBuffer& spMsg, StunTransactionId* pTransId)
{
    HRESULT hr = S_OK;
    CStunMessageReader reader;
    CStunMessageReader::ReaderParseState state;

    state = reader.AddBytes(spMsg->GetData(), spMsg->GetSize());
    ChkIfA(state != CStunMessageReader::BodyValidated, E_UNEXPECTED);

    ChkIfA(reader.GetMessageType() != StunMsgTypeBinding, E_UNEXPECTED);

    reader.GetTransactionId(pTransId);

    ChkIfA(false == IsTransactionIdValid(*pTransId), E_FAIL);

Cleanup:
    return hr;
}