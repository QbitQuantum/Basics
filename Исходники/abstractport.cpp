void AbstractPort::updatePacketListInterleaved()
{
    int numStreams = 0;
    quint64 minGap = ULLONG_MAX;
    quint64 duration = quint64(1e9);
    QList<quint64> ibg1, ibg2;
    QList<quint64> nb1, nb2;
    QList<quint64> ipg1, ipg2;
    QList<quint64> np1, np2;
    QList<ulong> schedSec, schedNsec;
    QList<ulong> pktCount, burstCount;
    QList<ulong> burstSize;
    QList<bool> isVariable;
    QList<QByteArray> pktBuf;
    QList<ulong> pktLen;

    qDebug("In %s", __FUNCTION__);

    // First sort the streams by ordinalValue
    qSort(streamList_.begin(), streamList_.end(), StreamBase::StreamLessThan);

    clearPacketList();

    for (int i = 0; i < streamList_.size(); i++)
    {
        if (!streamList_[i]->isEnabled())
            continue;

        double numBursts = 0;
        double numPackets = 0;

        quint64 _burstSize = 0;
        double ibg = 0;
        quint64 _ibg1 = 0, _ibg2 = 0;
        quint64 _nb1 = 0, _nb2 = 0;
        double ipg = 0;
        quint64 _ipg1 = 0, _ipg2 = 0;
        quint64 _np1 = 0, _np2 = 0;

        switch (streamList_[i]->sendUnit())
        {
        case OstProto::StreamControl::e_su_bursts:
            numBursts = streamList_[i]->burstRate();
            if (streamList_[i]->burstRate() > 0)
            {
                ibg = 1e9/double(streamList_[i]->burstRate());
                _ibg1 = quint64(ceil(ibg));
                _ibg2 = quint64(floor(ibg));
                _nb1 = quint64((ibg - double(_ibg2)) * double(numBursts));
                _nb2 = quint64(numBursts) - _nb1;
                _burstSize = streamList_[i]->burstSize();
            }
            break;
        case OstProto::StreamControl::e_su_packets:
            numPackets = streamList_[i]->packetRate();
            if (streamList_[i]->packetRate() > 0)
            {
                ipg = 1e9/double(streamList_[i]->packetRate());
                _ipg1 = llrint(ceil(ipg));
                _ipg2 = quint64(floor(ipg));
                _np1 = quint64((ipg - double(_ipg2)) * double(numPackets));
                _np2 = quint64(numPackets) - _np1;
                _burstSize = 1;
            }
            break;
        default:
            qWarning("Unhandled stream control unit %d",
                streamList_[i]->sendUnit());
            continue;
        }
        qDebug("numBursts = %g, numPackets = %g\n", numBursts, numPackets);

        qDebug("ibg  = %g", ibg);
        qDebug("ibg1 = %" PRIu64, _ibg1);
        qDebug("nb1  = %" PRIu64, _nb1);
        qDebug("ibg2 = %" PRIu64, _ibg2);
        qDebug("nb2  = %" PRIu64 "\n", _nb2);

        qDebug("ipg  = %g", ipg);
        qDebug("ipg1 = %" PRIu64, _ipg1);
        qDebug("np1  = %" PRIu64, _np1);
        qDebug("ipg2 = %" PRIu64, _ipg2);
        qDebug("np2  = %" PRIu64 "\n", _np2);


        if (_ibg2 && (_ibg2 < minGap))
            minGap = _ibg2;

        if (_ibg1 && (_ibg1 > duration))
            duration = _ibg1;

        ibg1.append(_ibg1);
        ibg2.append(_ibg2);

        nb1.append(_nb1);
        nb2.append(_nb1);

        burstSize.append(_burstSize);

        if (_ipg2 && (_ipg2 < minGap))
            minGap = _ipg2;

        if (_np1)
        {
            if (_ipg1 && (_ipg1 > duration))
                duration = _ipg1;
        }
        else
        {
            if (_ipg2 && (_ipg2 > duration))
                duration = _ipg2;
        }

        ipg1.append(_ipg1);
        ipg2.append(_ipg2);

        np1.append(_np1);
        np2.append(_np1);

        schedSec.append(0);
        schedNsec.append(0);

        pktCount.append(0);
        burstCount.append(0);

        if (streamList_[i]->isFrameVariable())
        {
            isVariable.append(true);
            pktBuf.append(QByteArray());
            pktLen.append(0);
        }
        else
        {
            isVariable.append(false);
            pktBuf.append(QByteArray());
            pktBuf.last().resize(kMaxPktSize);
            pktLen.append(streamList_[i]->frameValue(
                    (uchar*)pktBuf.last().data(), pktBuf.last().size(), 0));
        }

        numStreams++;
    } // for i

    qDebug("minGap   = %" PRIu64, minGap);
    qDebug("duration = %" PRIu64, duration);

    uchar* buf;
    int len;
    quint64 durSec = duration/ulong(1e9);
    quint64 durNsec = duration % ulong(1e9);
    quint64 sec = 0; 
    quint64 nsec = 0;
    quint64 lastPktTxSec = 0;
    quint64 lastPktTxNsec = 0;
    do
    {
        for (int i = 0; i < numStreams; i++)
        {
            // If a packet is not scheduled yet, look at the next stream
            if ((schedSec.at(i) > sec) || (schedNsec.at(i) > nsec))
                continue;

            for (uint j = 0; j < burstSize[i]; j++)
            {
                if (isVariable.at(i))
                {
                    buf = pktBuf_;
                    len = streamList_[i]->frameValue(pktBuf_, sizeof(pktBuf_), 
                            pktCount[i]);
                }
                else
                {
                    buf = (uchar*) pktBuf.at(i).data();
                    len = pktLen.at(i);
                }

                if (len <= 0)
                    continue;

                qDebug("q(%d) sec = %" PRIu64 " nsec = %" PRIu64, i, sec, nsec);
                appendToPacketList(sec, nsec, buf, len); 
                lastPktTxSec = sec;
                lastPktTxNsec = nsec;

                pktCount[i]++;
                schedNsec[i] += (pktCount.at(i) < np1.at(i)) ? 
                    ipg1.at(i) : ipg2.at(i);
                while (schedNsec.at(i) >= 1e9)
                {
                    schedSec[i]++;
                    schedNsec[i] -= long(1e9);
                }
            }

            burstCount[i]++;
            schedNsec[i] += (burstCount.at(i) < nb1.at(i)) ? 
                    ibg1.at(i) : ibg2.at(i);
            while (schedNsec.at(i) >= 1e9)
            {
                schedSec[i]++;
                schedNsec[i] -= long(1e9);
            }
        } 

        nsec += minGap;
        while (nsec >= 1e9)
        {
            sec++;
            nsec -= long(1e9);
        }
    } while ((sec < durSec) || (nsec < durNsec));

    qint64 delaySec = durSec - lastPktTxSec;
    qint64 delayNsec = durNsec - lastPktTxNsec;
    while (delayNsec < 0)
    {
        delayNsec += long(1e9);
        delaySec--;
    }
    qDebug("loop Delay = %" PRId64 "/%" PRId64, delaySec, delayNsec);
    setPacketListLoopMode(true, delaySec, delayNsec); 
    isSendQueueDirty_ = false;
}