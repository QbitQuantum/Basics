/*virtual*/
std::string CCopasiObject::getObjectDisplayName(bool regular /*=true*/, bool richtext /*=false*/) const
{
  std::string ret = "";

  if (mpObjectParent)
    {
      ret = mpObjectParent->getObjectDisplayName(regular, richtext);

      if (ret == "(CN)Root" ||
          ret == "ModelList[]" ||
          ret.substr(0, 7) == "(Model)")
        {
          ret = "";
        }
    }

  if (ret.length() >= 2)
    if ((ret.substr(ret.length() - 2) == "[]") && (!isReference()))
      {
        ret.insert(ret.length() - 1, getObjectName());

        if (isNameVector() || isVector() || getObjectType() == "ParameterGroup")
          ret += "[]";

        return ret;
      }

  if ((ret.length() != 0) && (ret[ret.length() - 1] != '.'))
    ret += ".";

  if (isNameVector() || isVector() || getObjectType() == "ParameterGroup")
    ret += getObjectName() + "[]";
  else if (isReference()
           || getObjectType() == "Parameter"
           || getObjectType() == getObjectName())
    ret += getObjectName();
  else
    ret += "(" + getObjectType() + ")" + getObjectName();

  return ret;
}