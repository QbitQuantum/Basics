static bool findFileWrapper(const String& file, void* ctx) {
  ResolveIncludeContext* context = (ResolveIncludeContext*)ctx;
  assert(context->path.isNull());

  Stream::Wrapper* w = Stream::getWrapperFromURI(file);
  if (!dynamic_cast<FileStreamWrapper*>(w)) {
    if (w->stat(file, context->s) == 0) {
      context->path = file;
      return true;
    }
  }

  // handle file://
  if (file.substr(0, 7) == s_file_url) {
    return findFileWrapper(file.substr(7), ctx);
  }

  // TranslatePath() will canonicalize the path and also check
  // whether the file is in an allowed directory.
  String translatedPath = File::TranslatePathKeepRelative(file);
  if (file[0] != '/') {
    if (HPHP::Eval::FileRepository::findFile(translatedPath.get(),
                                             context->s)) {
      context->path = translatedPath;
      return true;
    }
    return false;
  }
  if (RuntimeOption::SandboxMode || !RuntimeOption::AlwaysUseRelativePath) {
    if (HPHP::Eval::FileRepository::findFile(translatedPath.get(),
                                             context->s)) {
      context->path = translatedPath;
      return true;
    }
  }
  string server_root(SourceRootInfo::GetCurrentSourceRoot());
  if (server_root.empty()) {
    server_root = string(g_vmContext->getCwd()->data());
    if (server_root.empty() || server_root[server_root.size() - 1] != '/') {
      server_root += "/";
    }
  }
  String rel_path(Util::relativePath(server_root, translatedPath.data()));
  if (HPHP::Eval::FileRepository::findFile(rel_path.get(),
                                           context->s)) {
    context->path = rel_path;
    return true;
  }
  return false;
}