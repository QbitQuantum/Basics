void EsealBDOperationError (CPU_INT8U error, FNCT_COMM comm)
{
    CPU_INT8U  data[SOCKET_HEAD_SIZE + CHIPHERTEXT_HEAD_SIZE + HEAD_HEAD_SIZE + ESEALBD_OPERATION_REPLAY_SIZE_ERROR];
    CPU_INT16U len;
    CPU_INT32U id;
    CPU_INT32U rn;
    CPU_INT32U key;
    sCiphertextTypeDef *ciphertext;
    CPU_INT8U *p;
    sHeadTypeDef *head;
    sEsealBDOperatioErrornReplayTypeDef *replay;
    
    id  = EsealBDGetID();
    rn  = EsealBDGetRN();
    key = EsealBDGetKey();
    
    ciphertext = (sCiphertextTypeDef *)&data[SOCKET_HEAD_SIZE];
    ciphertext->id  = NToHL(id);
    ciphertext->rn  = NToHL(rn);
    
    ciphertext->len = NToHS(HEAD_HEAD_SIZE + ESEALBD_OPERATION_REPLAY_SIZE_ERROR);
    
    p = (CPU_INT8U *)&ciphertext->data;
    
    head = (sHeadTypeDef *)p;
    
    replay = (sEsealBDOperatioErrornReplayTypeDef *)&head->data;
    
    replay->id = NToHL(id);
    replay->error = error;
    
    len  = ESEALBD_OPERATION_REPLAY_SIZE_ERROR;
    head->len = NToHS(len);
    head->type = NToHS(ESEALBD_OPERATION_TYPE_REPLAY_ERROR);
    head->crc = NToHS(GetCRC16(&data[SOCKET_HEAD_SIZE + CHIPHERTEXT_HEAD_SIZE + HEAD_CRC_POS],
                               HEAD_HEAD_SIZE - HEAD_CRC_LEN + len)); 
    
    Encrypt(id, rn, key, (CPU_INT8U *)&ciphertext->data, NToHS(ciphertext->len));
    
    SocketPackageSend(ESEALBD_OPERATION_PORT, data, CHIPHERTEXT_HEAD_SIZE + HEAD_HEAD_SIZE + len); 
    comm(data, SOCKET_HEAD_SIZE + CHIPHERTEXT_HEAD_SIZE + HEAD_HEAD_SIZE + len);
}