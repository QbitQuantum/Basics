int CpduTournamentParams::sendTournamentParams(CBaseTournamentQueue* queue,
                                               u_int16_t flag,
                                               u_int32_t p1,
                                               u_int32_t p2)
{
    int rc = 0;
    pdu_tournamentparams pdu;
    memset(&pdu, 0, sizeof(pdu));

    pdu.flag = htons(flag);
    pdu.param1 = htonl(p1);
    pdu.param2 = htonl(p2);

    memcpy(value_ + PDU_HEADER_SIZE, &pdu, sizeof(pdu));

    TableList& tl = queue->getTableList();
    for (TableList::iterator tb = tl.begin(),
                             te = tl.end();
         tb != te;
         ++tb)
    {
        rc = sendTo((*tb)->getSocket());
    }

    return rc;
}