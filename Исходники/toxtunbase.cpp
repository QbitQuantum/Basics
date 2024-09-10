int ToxTunBase::peerRemoveChan(ENetPeer *enpeer, ToxTunChannel *chan)
{
    ToxTunChannel *tchan0 = (ToxTunChannel*)enpeer->ENET_PEER_TOXCHAN;
    assert(tchan0 == chan);
    enpeer->ENET_PEER_TOXCHAN = NULL;
    return 0;
    //
    QVector<ToxTunChannel*>* chans = (QVector<ToxTunChannel*>*)enpeer->ENET_PEER_TOXCHAN;
    int idx = -1;
    ToxTunChannel *tchan = NULL;
    
    for (int i = 0; i < chans->count(); i++) {
        tchan = chans->at(i);
        if (tchan == chan) {
            idx = i;
            break;
        }
    }

    if (idx ==  -1) {
        qDebug()<<"chan not found:"<<chan<<chan->m_conid;
        return idx;
    }

    chans->remove(idx);
    
    return idx;
}