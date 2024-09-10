/**
  * Slot responding on a change of a masking shape.
  */
void InstrumentWindowMaskTab::shapeChanged()
{
  if (!m_left) return; // check that everything is ok
  m_userEditing = false; // this prevents resetting shape proeprties by doubleChanged(...)
  RectF rect = m_instrWindow->getSurface()->getCurrentBoundingRect();
  m_doubleManager->setValue(m_left,rect.x0());
  m_doubleManager->setValue(m_top,rect.y1());
  m_doubleManager->setValue(m_right,rect.x1());
  m_doubleManager->setValue(m_bottom,rect.y0());
  for(QMap<QtProperty *,QString>::iterator it = m_doublePropertyMap.begin(); it != m_doublePropertyMap.end(); ++it)
  {
    m_doubleManager->setValue(it.key(),m_instrWindow->getSurface()->getCurrentDouble(it.value()));
  }
  for(QMap<QString,QtProperty *>::iterator it = m_pointPropertyMap.begin(); it != m_pointPropertyMap.end(); ++it)
  {
    QtProperty* prop = it.value();
    QList<QtProperty*> subs = prop->subProperties();
    if (subs.size() != 2) continue;
    QPointF p = m_instrWindow->getSurface()->getCurrentPoint(it.key());
    m_doubleManager->setValue(subs[0],p.x());
    m_doubleManager->setValue(subs[1],p.y());
  }
  m_userEditing = true;
}