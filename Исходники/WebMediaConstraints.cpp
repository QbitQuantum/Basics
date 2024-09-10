WebString StringConstraint::toString() const {
  StringBuilder builder;
  builder.append('{');
  if (!m_ideal.isEmpty()) {
    builder.append("ideal: [");
    bool first = true;
    for (const auto& iter : m_ideal) {
      if (!first)
        builder.append(", ");
      builder.append('"');
      builder.append(iter);
      builder.append('"');
      first = false;
    }
    builder.append(']');
  }
  if (!m_exact.isEmpty()) {
    if (builder.length() > 1)
      builder.append(", ");
    builder.append("exact: [");
    bool first = true;
    for (const auto& iter : m_exact) {
      if (!first)
        builder.append(", ");
      builder.append('"');
      builder.append(iter);
      builder.append('"');
    }
    builder.append(']');
  }
  builder.append('}');
  return builder.toString();
}