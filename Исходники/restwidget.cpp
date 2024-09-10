void RestWidget::parseOrderUrls(QNetworkReply *reply){

    if(reply->error()>0){
        xmloutput->addItem(QTime::currentTime().toString() +" : " + reply->errorString());
        emit connectionError();

    } else{
        QByteArray data = reply->readAll();
        QDomDocument doc;

        dataOutput->setText(data);

        doc.setContent(data);

        QDomNodeList orderNodes = doc.elementsByTagName("order");

        for(int i = 0; i < orderNodes.size(); i++){
            xmloutput->addItem(orderNodes.at(i).toElement().text());
            orderIDs->append(orderNodes.at(i).toElement().text());
        }
        order_ptr = 0; //reset the order pointer.
    }
    QObject::disconnect(netManager2, SIGNAL(finished(QNetworkReply*)),this, SLOT(parseOrderUrls(QNetworkReply*)));
}