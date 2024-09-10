void UnwrappedSurface::zoom() {
  if (!m_viewImage)
    return;
  RectF newView = selectionRectUV();
  if (newView.isEmpty())
    return;
  m_zoomStack.push(m_viewRect);
  m_viewRect = newView;
  updateView();
  emptySelectionRect();
  emit updateInfoText();
}