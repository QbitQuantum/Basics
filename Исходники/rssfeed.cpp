void RssFeedNode::render(Grantlee::OutputStream* stream, Grantlee::Context* c)
{
  QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
  QUrl url(Grantlee::getSafeString(m_url.resolve(c)));
  QNetworkReply *reply = mgr->get(QNetworkRequest(url));
  QEventLoop eLoop;
  connect( mgr, SIGNAL( finished( QNetworkReply * ) ), &eLoop, SLOT( quit() ) );
  eLoop.exec( QEventLoop::ExcludeUserInputEvents );

  c->push();
  foreach(Grantlee::Node *n, m_childNodes) {
    if (!n->inherits(XmlNamespaceNode::staticMetaObject.className()))
      continue;
    Grantlee::OutputStream _dummy;
    n->render(&_dummy, c);
  }

  QXmlQuery query;
  QByteArray ba = reply->readAll();

  QBuffer buffer;
  buffer.setData(ba);
  buffer.open(QIODevice::ReadOnly);
  query.bindVariable("inputDocument", &buffer);
  QString ns;
  QHash<QString, QVariant> h = c->lookup("_ns").toHash();
  QHash<QString, QVariant>::const_iterator it = h.constBegin();
  const QHash<QString, QVariant>::const_iterator end = h.constEnd();
  for ( ; it != end; ++it ) {
    if (it.key().isEmpty()) {
      ns += QLatin1Literal( "declare default element namespace " ) + QLatin1Literal( " \"" ) + it.value().toString() + QLatin1Literal( "\";\n" );
    } else {
      ns += QLatin1Literal( "declare namespace " ) + it.key() + QLatin1Literal( " = \"" ) + it.value().toString() + QLatin1Literal( "\";\n" );
    }
  }
  query.setQuery(ns + "doc($inputDocument)" + Grantlee::getSafeString(m_query.resolve(c)).get());

  QXmlResultItems result;
  query.evaluateTo(&result);

  QXmlItem item(result.next());
  int count = 0;
  while (!item.isNull()) {
      if (count++ > 20)
        break;
      query.setFocus(item);
      c->push();
      foreach(Grantlee::Node *n, m_childNodes) {
        if (n->inherits(XmlNamespaceNode::staticMetaObject.className()))
          continue;
        c->insert("_q", QVariant::fromValue(query));
        n->render(stream, c);
      }
      c->pop();
      item = result.next();
  }
  c->pop();
}