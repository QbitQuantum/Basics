void ContextPropertyPrivate::subscribe() {
  if (m_conn) {
    return;
  }

  m_conn = new Connection(m_key.toStdString());

  m_conn->connect([this](const std::string& val) {
      // Called from an arbitrary thread

      QMutexLocker l(&m_lock);
      m_value = QVariant(QString::fromStdString(val));
      QMetaObject::invokeMethod(m_parent, "valueChanged", Qt::QueuedConnection);
    });
}