void
ScXMLStringDataObj::convertToString(SbString & str) const
{
  if (!this->value) {
    str = "''";
  } else {
    // FIXME: quote special characters (')
    str.sprintf("'%s'", this->value);
  }
}