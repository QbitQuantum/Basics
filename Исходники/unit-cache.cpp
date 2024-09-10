bool findFileWrapper(const String& file, void* ctx) {
  auto const context = static_cast<ResolveIncludeContext*>(ctx);
  assertx(context->path.isNull());

  Stream::Wrapper* w = Stream::getWrapperFromURI(file);
  if (w && !w->isNormalFileStream()) {
    // Stream wrappers can reenter PHP via user defined callbacks. Roll this
    // operation into a single event
    rqtrace::EventGuard trace{"STREAM_WRAPPER_STAT"};
    rqtrace::DisableTracing disable;

    if (w->stat(file, context->s) == 0) {
      context->path = file;
      return true;
    }
  }

  // handle file://
  if (StringUtil::IsFileUrl(file)) {
    return findFileWrapper(file.substr(7), ctx);
  }

  if (!w) return false;

  auto passW =
    RuntimeOption::RepoAuthoritative ||
    dynamic_cast<FileStreamWrapper*>(w) ||
    !w->isNormalFileStream()
      ? nullptr
      : w;

  // TranslatePath() will canonicalize the path and also check
  // whether the file is in an allowed directory.
  String translatedPath = File::TranslatePathKeepRelative(file);
  if (!FileUtil::isAbsolutePath(file.toCppString())) {
    if (findFile(translatedPath.get(), context->s, context->allow_dir,
                 passW, context->nativeFuncs)) {
      context->path = translatedPath;
      return true;
    }
    return false;
  }
  if (RuntimeOption::SandboxMode || !RuntimeOption::AlwaysUseRelativePath) {
    if (findFile(translatedPath.get(), context->s, context->allow_dir, passW,
                 context->nativeFuncs)) {
      context->path = translatedPath;
      return true;
    }
  }
  std::string server_root(SourceRootInfo::GetCurrentSourceRoot());
  if (server_root.empty()) {
    server_root = std::string(g_context->getCwd().data());
    if (server_root.empty() ||
        FileUtil::isDirSeparator(server_root[server_root.size() - 1])) {
      server_root += FileUtil::getDirSeparator();
    }
  }
  String rel_path(FileUtil::relativePath(server_root, translatedPath.data()));
  if (findFile(rel_path.get(), context->s, context->allow_dir, passW,
               context->nativeFuncs)) {
    context->path = rel_path;
    return true;
  }
  return false;
}