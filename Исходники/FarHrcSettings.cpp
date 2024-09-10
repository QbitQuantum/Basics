void FarHrcSettings::UpdatePrototype(Element *elem, bool userValue)
{
  const String *typeName = elem->getAttribute(DString("name"));
  if (typeName == null){
    return;
  }
  HRCParser *hrcParser = parserFactory->getHRCParser();
  FileTypeImpl *type = (FileTypeImpl *)hrcParser->getFileType(typeName);
  if (type== null){
    return;
  };
  for(Node *content = elem->getFirstChild(); content != null; content = content->getNextSibling()){
    if (*content->getNodeName() == "param"){
      const String *name = ((Element*)content)->getAttribute(DString("name"));
      const String *value = ((Element*)content)->getAttribute(DString("value"));
      const String *descr = ((Element*)content)->getAttribute(DString("description"));
      if (name == null || value == null){
        continue;
      };

      if (type->getParamValue(SString(name))==null){
        type->addParam(name);
      }
      if (descr != null){
        type->setParamDescription(SString(name), descr);
      }
      if (userValue){
        delete type->getParamNotDefaultValue(DString(name));
        type->setParamValue(SString(name), value);
      }
      else{
        delete type->getParamDefaultValue(DString(name));
        type->setParamDefaultValue(SString(name), value);
      }
    };
  };
}