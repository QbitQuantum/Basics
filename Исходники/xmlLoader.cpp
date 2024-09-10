void XmlLoader::readStylus(QDomElement const &stylus)
{
    QDomNodeList stylusAttributes = stylus.childNodes();

    Stylus* stylusItem = new Stylus(0, 0, NULL);
    for (unsigned i = 0; i < stylusAttributes.length(); ++i) {
        QDomElement type = stylusAttributes.at(i).toElement();
        if (type.tagName() == "line") {
            QRectF rect = readRectOfXandY(type);
            Line* item = new Line(rect.left(), rect.top(), rect.right(), rect.bottom(), NULL);
            item->readPenBrush(type);
            stylusItem->mListLine.push_back(item);
            stylusItem->setPen(item->pen());
            stylusItem->setBrush(item->brush());
        }
        else
            qDebug() << "Incorrect stylus tag";
    }
    mScene->addItem(stylusItem);
    mScene->setZValue(stylusItem);
}