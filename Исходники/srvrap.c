/*
================

    PFBYTE inBuf - The start of the incoming buffer (needed for offset calculations)
    PSMB_TRANSACTIONRQ pInReq - the incoming request
    PFBYTE outBuf - the outgoing buffer (needed for offset calculations)
    PSMB_TRANSACTIONRS pOutRes - The out going transaction response
================
*/
int RAP_Proc (PSMB_SESSIONCTX pCtx,
    PRTSMB_HEADER pInHdr, PRTSMB_TRANSACTION pTransaction, PFVOID pInBuf,
    PRTSMB_HEADER pOutHdr, PRTSMB_TRANSACTION_R pTransactionR, rtsmb_size size_left)
{
    RTSMB_RAP_REQUEST func;
    rtsmb_char param [50];
    rtsmb_char answer [50];
    int size, data_size = 0;
    word param_size;

    func.parent = pTransaction;
    func.parameter = param;
    func.parameter_size = 49;
    func.answer = answer;
    func.answer_size = 49;
    size = srv_cmd_read_rap_request (pCtx->read_origin, pInBuf,
         pCtx->current_body_size - (rtsmb_size)(PDIFF (pInBuf, pCtx->read_origin)), pInHdr, &func);
    if (size == -1) return 0;
    pInBuf = PADD (pInBuf, size);

    param_size = 0;
    switch (func.opcode)
    {
    case RAP_COM_NET_SHARE_ENUM:
        data_size = NetShareEnum (pCtx, &func, pInHdr, pInBuf, pOutHdr,
            size_left, &param_size);
        break;
    case RAP_COM_NET_SERVER_GETINFO:
        data_size = NetServerGetInfo (pCtx, &func, pInHdr, pInBuf, pOutHdr,
            size_left, &param_size);
        break;
    case RAP_COM_NET_WKSTA_GETINFO:
        data_size = NetWkstaGetInfo (pCtx, &func, pInHdr, pInBuf, pOutHdr,
            size_left, &param_size);
        break;
    case RAP_COM_NET_SHARE_GETINFO:
        data_size = NetShareGetInfo (pCtx, &func, pInHdr, pInBuf, pOutHdr,
            size_left, &param_size);
        break;
    case RAP_COM_WPRINTQ_GETINFO:
        data_size = WPrintQGetInfo (pCtx, &func, pInHdr, pInBuf, pOutHdr,
            size_left, &param_size);
        break;
    case RAP_COM_NET_SERVER_ENUM2:
        data_size = NetServerEnum2 (pCtx, &func, pInHdr, pInBuf, pOutHdr,
            size_left, &param_size);
        break;
        /*
    case RAP_COM_NET_ACCESS_GETINFO:
        NetAccessGetInfo (pCtx, &func, pInHdr, pInBuf, pOutHdr, size_left);
        break;*/
    default:
        RTSMB_DEBUG_OUTPUT_STR ("RAP_Proc: function unhandled: ", RTSMB_DEBUG_TYPE_ASCII);
        RTSMB_DEBUG_OUTPUT_INT (func.opcode);
        RTSMB_DEBUG_OUTPUT_STR ("\n", RTSMB_DEBUG_TYPE_ASCII);
    }

    if (data_size == -2) /* special error case where we don't want to answer */
        return -1;

    pTransactionR->setup_size = 0;
    pTransactionR->setup = (PFWORD)0;
    pTransactionR->parameter = pCtx->tmpBuffer;
    pTransactionR->parameter_count = param_size;
    if (data_size == -1)
    {
        pTransactionR->data = (PFBYTE)0;
        pTransactionR->data_count = 0;
    }
    else
    {
        pTransactionR->data = PADD (pCtx->tmpBuffer, param_size);
        pTransactionR->data_count = (word) data_size;
    }

    return 0;
} // End RAP_Proc