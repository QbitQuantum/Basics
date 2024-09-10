/*!
  Creates an instance of a suitable SoForeignFileKit subtype.
  Returns NULL on failure or a kit with refcount of 1 on success.
*/
static SoForeignFileKit *create_foreignfilekit(const char *filename, SbBool exhaust)
{
  assert(SoForeignFileKitP::fileexts != NULL);

  const char * extptr = strrchr(filename, '.');
  if (extptr) {
    extptr++;
    SbName ext(SbString(extptr).lower());
    SoType handler = SoType::badType();
    if (SoForeignFileKitP::fileexts->get(ext.getString(), handler)) {
      SoForeignFileKit * foreignfile = (SoForeignFileKit *)handler.createInstance();
      foreignfile->ref();
      if (foreignfile->canReadFile(filename)) {
        return foreignfile;
      }
      else {
        foreignfile->unref();
      }
    }
    else {
      // We try to synthesize a classname from the extension (e.g. SoFBXFileKit),
      // and load it using the SoType autoloader feature.
      SbString filekitname;
      filekitname.sprintf("So%sFileKit", SbString(ext.getString()).upper().getString());
      SoType filekittype = SoType::fromName(SbName(filekitname));
      if (!filekittype.isBad()) return create_foreignfilekit(filename, exhaust);

      // FIXME: Some filekits supports more than one file format/extension (e.g. FBX).
      // We need a way of mapping extensions to library, or a way of loading
      // each external kit and testing for support.
      // FIXME: Temporary hack: Load SoFBXFileKit
      filekitname = "SoFBXFileKit";
      filekittype = SoType::fromName(SbName(filekitname));
      if (!filekittype.isBad()) return create_foreignfilekit(filename, exhaust);
    }
  }
  if (exhaust) {
    // FIXME: Implement
    // SoForeignFileKitP::fileexts->apply()
  }
  return NULL;
}