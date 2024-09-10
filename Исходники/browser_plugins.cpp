inline void genSafariExtension(const std::string& uid,
                               const std::string& path,
                               QueryData& results) {
  Row r;
  r["uid"] = uid;
  r["path"] = path;

  // Loop through (Plist key -> table column name) in kSafariExtensionKeys.
  struct archive* ext = archive_read_new();
  if (ext == nullptr) {
    return;
  }

  // Perform a dry run of the file read.
  if (!readFile(path).ok()) {
    return;
  }

  // Finally drop privileges to the user controlling the extension.
  auto dropper = DropPrivileges::get();
  if (!dropper->dropToParent(path)) {
    return;
  }

  // Use open_file, instead of the preferred open_filename for OS X 10.9.
  archive_read_support_format_xar(ext);
  if (archive_read_open_filename(ext, path.c_str(), 10240) != ARCHIVE_OK) {
    archive_read_finish(ext);
    return;
  }

  struct archive_entry* entry = nullptr;
  while (archive_read_next_header(ext, &entry) == ARCHIVE_OK) {
    auto item_path = archive_entry_pathname(entry);
    // Documentation for libarchive mentions these APIs may return NULL.
    if (item_path == nullptr) {
      archive_read_data_skip(ext);
      continue;
    }

    // Assume there is no non-root Info.
    if (std::string(item_path).find("Info.plist") == std::string::npos) {
      archive_read_data_skip(ext);
      continue;
    }

    // Read the decompressed Info.plist content.
    auto content = std::string(archive_entry_size(entry), '\0');
    archive_read_data_into_buffer(ext, &content[0], content.size());

    // If the Plist can be parsed, extract important keys into columns.
    pt::ptree tree;
    if (parsePlistContent(content, tree).ok()) {
      for (const auto& it : kSafariExtensionKeys) {
        r[it.second] = tree.get(it.first, "");
      }
    }
    break;
  }

  archive_read_close(ext);
  archive_read_finish(ext);
  results.push_back(std::move(r));
}