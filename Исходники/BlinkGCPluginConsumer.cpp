bool BlinkGCPluginConsumer::InCheckedNamespace(RecordInfo* info) {
  if (!info)
    return false;
  for (DeclContext* context = info->record()->getDeclContext();
       !context->isTranslationUnit();
       context = context->getParent()) {
    if (NamespaceDecl* decl = dyn_cast<NamespaceDecl>(context)) {
      if (decl->isAnonymousNamespace())
        return true;
      if (options_.checked_namespaces.find(decl->getNameAsString()) !=
          options_.checked_namespaces.end()) {
        return true;
      }
    }
  }
  return false;
}