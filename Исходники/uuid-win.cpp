RTDECL(bool)  RTUuidIsNull(PCRTUUID pUuid)
{
    /* check params */
    AssertPtrReturn(pUuid, true);

    RPC_STATUS status;
    return !!UuidIsNil((UUID *)pUuid, &status);
}