std::vector<SimXmlElement> SimXmlDoc::getElements(const std::string& elementName) const
{
  std::vector<SimXmlElement> result;

  if (isNull()){
    return result;
  }

  QString queryString = simQuery("/SimModel/" + elementName);

  QXmlQuery query;
  QDomNodeModel model(query.namePool(), *(impl()));
  query.setFocus(QXmlItem(model.fromDomNode(impl()->documentElement())));
  query.setQuery(queryString, QUrl(QString::fromStdString(this->path())));

  if (query.isValid()) {

    QString junk;

    QXmlResultItems items;

    query.evaluateTo(&items);

    QXmlItem item(items.next());

    while (!item.isNull()) {

      QDomElement elem = model.toDomNode(item.toNodeModelIndex()).toElement();

      QSharedPointer<QDomElement> impl(new QDomElement(elem));

      result.push_back(SimXmlElement(impl, *this));

      // get next item
      item = items.next();
    }
  }

  return result;
}