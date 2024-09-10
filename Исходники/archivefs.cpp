int archivefs_rename(const char* old_path, const char* new_path) {
  char fpath_old[PATH_MAX];
  fullpath(fpath_old, old_path);

  /* pro fyzické soubory je třeba opět rozvinou nové jméno, jinak by byl
   * soubor vytvořen v pracovním adresáři procesu
   */
  char fpath_new[PATH_MAX];
  fullpath(fpath_new, new_path);

  FileSystem* fs;
  FileNode* node;
  int ret;

  if (!getFile(fpath_old, &fs, &node)) {
    ret = rename(fpath_old, fpath_new);
    if (ret) {
      ret = errno;
      print_err("RENAME", old_path, ret);
    }
    return -ret;
  }

  /* Přejmenovává se celý archív */
  if (node->type == FileNode::ROOT_NODE) {
    ret = rename(fpath_old, fpath_new);
    if (ret) {
      ret = errno;
      print_err("RENAME", old_path, ret);
      return -ret;
    }
    FusePrivate* data = PRIVATE_DATA;

    data->filesystems->erase(fpath_old);
    free((void*)fs->archive_name);
    fs->archive_name = strdup(fpath_new);
    data->filesystems->insert(fs);
    return 0;
  }

  char* new_name;
  parsePathName(fpath_new, &new_name);
  ret = fs->rename(node, new_name);
  if (ret)
    print_err("RENAME", old_path, ret);

  return -ret;
}