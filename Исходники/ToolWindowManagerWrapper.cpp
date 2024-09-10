QVariantMap ToolWindowManagerWrapper::saveState() {
  if (layout()->count() > 1) {
    qWarning("too many children for wrapper");
    return QVariantMap();
  }
  if (isWindow() && layout()->count() == 0) {
    qWarning("empty top level wrapper");
    return QVariantMap();
  }
  QVariantMap result;
  result["geometry"] = saveGeometry().toBase64();
  QSplitter* splitter = findChild<QSplitter*>(QString(), Qt::FindDirectChildrenOnly);
  if (splitter) {
    result["splitter"] = m_manager->saveSplitterState(splitter);
  } else {
    ToolWindowManagerArea* area = findChild<ToolWindowManagerArea*>();
    if (area) {
      result["area"] = area->saveState();
    } else if (layout()->count() > 0) {
      qWarning("unknown child");
      return QVariantMap();
    }
  }
  return result;
}