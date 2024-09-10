Variant f_phpversion(const String& extension /* = null_string */) {
  Extension *ext;

  if (!extension) {
    return k_PHP_VERSION;
  }

  if ((ext = Extension::GetExtension(extension)) != nullptr &&
      strcmp(ext->getVersion(), NO_EXTENSION_VERSION_YET) != 0) {
    return ext->getVersion();
  }

  return false;
}