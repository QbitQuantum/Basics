bool RSContext::reflectToJava(const std::string &OutputPathBase,
                              const std::string &OutputPackageName,
                              const std::string &InputFileName,
                              const std::string &OutputBCFileName,
                              std::string *RealPackageName) {
  if (RealPackageName != NULL)
    RealPackageName->clear();

  const std::string &PackageName =
      ((OutputPackageName.empty()) ? mReflectJavaPackageName :
                                     OutputPackageName);
  if (PackageName.empty()) {
    clang::DiagnosticsEngine *DiagEngine = getDiagnostics();
    const clang::SourceManager *SM = getSourceManager();
    DiagEngine->Report(
        SM->getLocForEndOfFile(SM->getMainFileID()),
        DiagEngine->getCustomDiagID(clang::DiagnosticsEngine::Error,
                                    "missing \"#pragma rs "
                                    "java_package_name(com.foo.bar)\" "
                                    "in source file"));
    return false;
  }

  // Copy back the really applied package name
  RealPackageName->assign(PackageName);

  RSReflection *R = new RSReflection(this, mGeneratedFileNames);
  bool ret = R->reflect(OutputPathBase, PackageName,
                        InputFileName, OutputBCFileName);
  if (!ret)
    fprintf(stderr, "RSContext::reflectToJava : failed to do reflection "
                    "(%s)\n", R->getLastError());
  delete R;
  return ret;
}