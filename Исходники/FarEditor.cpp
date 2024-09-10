void FarEditor::reloadTypeSettings()
{
  FileType *ftype = baseEditor->getFileType();
  HRCParser *hrcParser = parserFactory->getHRCParser();

  FileType *def = hrcParser->getFileType(&DString("default"));
  if (def == null){
    throw Exception(DString("No 'default' file type found"));
  }

  int backparse = 2000;

  UnicodeTools::getNumber(def->getParamValue(DString("backparse")), &backparse);
  UnicodeTools::getNumber(def->getParamValue(DString("maxlinelength")), &maxLineLength);
  UnicodeTools::getNumber(def->getParamValue(DString("default-fore")), &newfore);
  UnicodeTools::getNumber(def->getParamValue(DString("default-back")), &newback);
  const String *value;
  value = def->getParamValue(DString("fullback"));
  if (value != null && value->equals("no")) fullBackground = false;
  value = def->getParamValue(DString("show-cross"));
  if (value != null && value->equals("none")){
    showHorizontalCross = false;
    showVerticalCross   = false;
  };
  if (value != null && value->equals("vertical")){
    showHorizontalCross = false;
    showVerticalCross   = true;
  };
  if (value != null && value->equals("horizontal")){
    showHorizontalCross = true;
    showVerticalCross   = false;
  };
  if (value != null && value->equals("both")){
    showHorizontalCross = true;
    showVerticalCross   = true;
  };
  value = def->getParamValue(DString("cross-zorder"));
  if (value != null && value->equals("top")) crossZOrder = 1;

  // installs custom file properties
  UnicodeTools::getNumber(ftype->getParamValue(DString("backparse")), &backparse);
  UnicodeTools::getNumber(ftype->getParamValue(DString("maxlinelength")), &maxLineLength);
  UnicodeTools::getNumber(ftype->getParamValue(DString("default-fore")), &newfore);
  UnicodeTools::getNumber(ftype->getParamValue(DString("default-back")), &newback);
  value = ftype->getParamValue(DString("fullback"));
  if (value != null && value->equals("no")) fullBackground = false;
  value = ftype->getParamValue(DString("show-cross"));
  if (value != null && value->equals("none")){
    showHorizontalCross = false;
    showVerticalCross   = false;
  };
  if (value != null && value->equals("vertical")){
    showHorizontalCross = false;
    showVerticalCross   = true;
  };
  if (value != null && value->equals("horizontal")){
    showHorizontalCross = true;
    showVerticalCross   = false;
  };
  if (value != null && value->equals("both")){
    showHorizontalCross = true;
    showVerticalCross   = true;
  };
  value = ftype->getParamValue(DString("cross-zorder"));
  if (value != null && value->equals("top")) crossZOrder = 1;

  baseEditor->setBackParse(backparse);
}