bool CQMedia::loadURL(const QString& url)
{
    QString tmp = url;
    tmp.remove(0,6);
    QString ip = tmp.split(QChar(':'))[0];
    int port = tmp.split(QChar(':'))[1].toInt();
    QUdpSocket udp;
    udp.bind(port,QUdpSocket::ShareAddress);
    udp.joinMulticastGroup(QHostAddress(ip));
    QEventLoop q;
    QTimer::singleShot(1000,&q,SLOT(quit()));

    connect(&udp,SIGNAL(readyRead()),&q,SLOT(quit()));
    q.exec();
    if(udp.pendingDatagramSize() == -1)
    {
        //qDebug("has no avalid datapkg...");
        QTimer::singleShot(3500,this,SLOT(_emitTimeout()));
        return false;
    }
    qDebug("has avalid datapkg...");
    udp.leaveMulticastGroup(QHostAddress(ip));
    udp.close();

    this->url = url;
//    SdpsrcParser sdpSrc(url);
//    if(!sdpSrc.isValid())
//    {
//        qDebug()<<"SdpsrcParser invalid!!";
//        return false;
//    }
//    sdpSrc.printf();
    GstElement *udpsrc =  gst_bin_get_by_name(GST_BIN(pipeline),"udpsrc");
    GstCaps *caps = gst_caps_new_simple("application/x-rtp",NULL);
    //QString uri = "udp://"+sdpSrc.broadcastIP+":"+QString::number(sdpSrc.v_port);
//    QString uri = "udp://"+sdpSrc.broadcastIP+":"+QString::number(sdpSrc.v_port);
   // QString uri = "udp://239.255.42.42:1234";
    QString uri = url;

    g_object_set(G_OBJECT(udpsrc),"uri",uri.toUtf8().data(),"caps",caps,NULL);
    gst_object_unref(udpsrc);
    return true;

}