bool MyMoneyXmlContentHandler::startElement(const QString& /* namespaceURI */, const QString& /* localName */, const QString& qName, const QXmlAttributes & atts)
{
  if (m_level == 0) {
    QString s = qName.toLower();
    if (s == "transaction"
        || s == "account"
        || s == "price"
        || s == "payee"
        || s == "tag"
        || s == "currency"
        || s == "security"
        || s == "keyvaluepairs"
        || s == "institution"
        || s == "report"
        || s == "budget"
        || s == "fileinfo"
        || s == "user"
        || s == "scheduled_tx"
        || s == "onlinejob") {
      m_baseNode = m_doc.createElement(qName);
      for (int i = 0; i < atts.count(); ++i) {
        m_baseNode.setAttribute(atts.qName(i), atts.value(i));
      }
      m_currNode = m_baseNode;
      m_level = 1;

    } else if (s == "transactions") {
      qDebug("reading transactions");
      if (atts.count()) {
        int count = atts.value(QLatin1String("count")).toInt();
        m_reader->signalProgress(0, count, i18n("Loading transactions..."));
        m_elementCount = 0;
      }
    } else if (s == "accounts") {
      qDebug("reading accounts");
      if (atts.count()) {
        int count = atts.value(QLatin1String("count")).toInt();
        m_reader->signalProgress(0, count, i18n("Loading accounts..."));
        m_elementCount = 0;
      }
    } else if (s == "securities") {
      qDebug("reading securities");
      if (atts.count()) {
        int count = atts.value(QLatin1String("count")).toInt();
        m_reader->signalProgress(0, count, i18n("Loading securities..."));
        m_elementCount = 0;
      }
    } else if (s == "currencies") {
      qDebug("reading currencies");
      if (atts.count()) {
        int count = atts.value(QLatin1String("count")).toInt();
        m_reader->signalProgress(0, count, i18n("Loading currencies..."));
        m_elementCount = 0;
      }
    } else if (s == "reports") {
      qDebug("reading reports");
      if (atts.count()) {
        int count = atts.value(QLatin1String("count")).toInt();
        m_reader->signalProgress(0, count, i18n("Loading reports..."));
        m_elementCount = 0;
      }
    } else if (s == "prices") {
      qDebug("reading prices");
      if (atts.count()) {
        int count = atts.value(QLatin1String("count")).toInt();
        m_reader->signalProgress(0, count, i18n("Loading prices..."));
        m_elementCount = 0;
      }
    } else if (s == "pricepair") {
      if (atts.count()) {
        m_reader->d->m_fromSecurity = atts.value(QLatin1String("from"));
        m_reader->d->m_toSecurity = atts.value(QLatin1String("to"));
      }
    }

  } else {
    m_level++;
    QDomElement node = m_doc.createElement(qName);
    for (int i = 0; i < atts.count(); ++i) {
      node.setAttribute(atts.qName(i), atts.value(i));
    }
    m_currNode.appendChild(node);
    m_currNode = node;
  }
  return true;
}