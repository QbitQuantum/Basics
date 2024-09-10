Array f_hphp_get_extension_info(CStrRef name) {
  Array ret;

  Extension *ext = Extension::GetExtension(name);

  ret.set("name",      name);
  ret.set("version",   ext ? ext->getVersion() : "");
  ret.set("info",      "");
  ret.set("ini",       Array::Create());
  ret.set("constants", Array::Create());
  ret.set("functions", Array::Create());
  ret.set("classes",   Array::Create());

  return ret;
}