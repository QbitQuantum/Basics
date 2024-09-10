CRect LayoutAttribute::getControlRect() const {
  return getWindowRect(m_manager.getWindow(), m_ctrlId);
}