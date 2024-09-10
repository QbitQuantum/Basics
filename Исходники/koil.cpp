void Koil::initialize(const QStringList & /*arguments*/, QString * /*errorString*/){

    wid = new KoilWidget();
    connect(wid, SIGNAL(printMessage(QString,msgType)),this,SIGNAL(printMessage(QString,msgType)));
}