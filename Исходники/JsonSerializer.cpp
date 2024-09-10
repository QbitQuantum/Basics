void JsonSerializer::addArray(const QVariantList &list) {
  m_buffer.append("[");
  for (int i = 0; i < list.length(); i++) {
    if (i > 0)
      m_buffer.append(",");
    addVariant(list[i]);
  }
  m_buffer.append("]");
}