ErrnoError remove_directory(const std::string& path, bool is_recursive) {
  if (path.empty()) {
    return make_error_perror("remove_directory", EINVAL);
  }

  std::string pr_path = prepare_path(path);
  if (pr_path[pr_path.length() - 1] == get_separator<char>()) {
    pr_path[pr_path.length() - 1] = 0;
  }

  const char* pr_path_ptr = pr_path.c_str();
  if (is_recursive) {
    DIR* dirp = opendir(pr_path_ptr);
    if (!dirp) {
      return ErrnoError();
    }

    struct dirent* p;
    while ((p = readdir(dirp)) != nullptr) {
      /* Skip the names "." and ".." as we don't want to recurse on them. */
      if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
        continue;
      }

      char pathBuffer[PATH_MAX] = {0};
      SNPrintf(pathBuffer, sizeof(pathBuffer), "%s/%s", path, p->d_name);
      struct stat statbuf;
      if (!::stat(pathBuffer, &statbuf)) {
        if (S_ISDIR(statbuf.st_mode)) {
          ErrnoError err = remove_directory(pathBuffer, is_recursive);
          if (err) {
            closedir(dirp);
            return err;
          }
        } else {
          ErrnoError err = remove_file(pathBuffer);
          if (err) {
            closedir(dirp);
            return err;
          }
        }
      }
    }
    closedir(dirp);
  }

  return do_rmdir_directory(pr_path_ptr);
}