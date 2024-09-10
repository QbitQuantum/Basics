bool gstIconManager::AddIcon(const std::string& path) {
  if (!Validate(path))
    return false;

  std::string base = khReplaceExtension(khBasename(path), ".png");
  std::string outfile = khComposePath(icon_path_[IconReference::External], base);

  if (CopyIcon(path, outfile) == true) {
    collection_[IconReference::External].push_back(gstIcon(
        base, IconReference::External));
    return true;
  }

  return false;
}