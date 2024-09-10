const ScXMLElt *
ScXMLLogElt::search(const char * attrname, const char * attrvalue) const
{
  const ScXMLElt * hit = inherited::search(attrname, attrvalue);
  if (hit) {
    return hit;
  }
  if (strcmp(attrname, "label") == 0) {
    if (this->label && strcmp(attrvalue, this->label) == 0) {
      return this;
    }
  }
  else if (strcmp(attrname, "expr") == 0) {
    if (this->expr && strcmp(attrvalue, this->expr) == 0) {
      return this;
    }
  }
  else if (strcmp(attrname, "level") == 0) {
    if (this->level && strcmp(attrvalue, this->level) == 0) {
      return this;
    }
  }
  return NULL;
}