const QString ctkLDAPExpr::fixupQString( const QString &s )
{
  QString sb;
  int len = s.length();
  for(int i=0; i<len; i++) {
    QChar c = s.at(i);
    if (!c.isSpace()) {
      if (c.isUpper())
        c = c.toLower();
      sb.append(c);
    }
  }
  return sb;
}