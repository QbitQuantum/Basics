void CullRect::updateCullRect(const AffineTransform& localToParentTransform) {
  if (m_rect != LayoutRect::infiniteIntRect())
    m_rect = localToParentTransform.inverse().mapRect(m_rect);
}