BOOL PEXPORT KppDDEPostAdvise(ATOMID idObjName, ATOMID idSlot)
{
    OBJECTID idLink = FindLink(LinkName(idObjName, idSlot));
    
    if (idLink)
    {
        ATOMID idTopic = Kpp_Get_SlotValue(OBJECT, idLink, Slot(idTopic));
        HSZ hszTopic = AtomToHsz(idTopic);
        WORD wLen = KppGetAtomName(idObjName, return_buffer, RET_BUFFER_LEN);
        BOOL bRes = FALSE;
        HSZ hszItem;
        
        return_buffer[wLen++] = ':';
        KppGetAtomName(idSlot, return_buffer + wLen, RET_BUFFER_LEN - wLen);
        hszItem = DdeCreateStringHandle(dwDDEInst, return_buffer, CP_WINANSI);
        
        if (hszTopic && hszItem)
            bRes = DdePostAdvise(dwDDEInst, hszTopic, hszItem);
        
        DdeFreeStringHandle(dwDDEInst, hszTopic);
        DdeFreeStringHandle(dwDDEInst, hszItem);

        return bRes;
    }
    
    return FALSE;
}