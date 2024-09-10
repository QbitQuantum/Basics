// Index any resources
void IndexRunner::indexRecognition(qint32 lid, Resource &r) {

    if (!keepRunning || pauseIndexing) {
        indexTimer->start();
        return;
    }

    // Make sure we have something to look through.
    Data recognition;
    if (r.recognition.isSet())
        recognition = r.recognition;
    if (!recognition.body.isSet())
        return;

    QDomDocument doc;
    QString emsg;
    doc.setContent(recognition.body, &emsg);

    // look for text tags
    QDomNodeList anchors = doc.documentElement().elementsByTagName("t");

    for (unsigned int i=0; keepRunning && !pauseIndexing && i<anchors.length(); i++) {
        QApplication::processEvents();
        QDomElement enmedia = anchors.at(i).toElement();
        QString weight = enmedia.attribute("w");
        QString text = enmedia.text();
        if (text != "") {
            IndexRecord *rec = new IndexRecord();
            rec->weight = weight.toInt();
            rec->lid = lid;
            rec->content = text;
            rec->source = "recognition";
            if (indexHash->contains(lid)) {
                delete indexHash->value(lid);
                indexHash->remove(lid);
            }
            indexHash->insert(lid, rec);
        }
    }
}