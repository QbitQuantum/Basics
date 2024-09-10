DocAccessible*
DocManager::CreateDocOrRootAccessible(nsIDocument* aDocument)
{
  // Ignore hidden documents, resource documents, static clone
  // (printing) documents and documents without a docshell.
  if (!aDocument->IsVisibleConsideringAncestors() ||
      aDocument->IsResourceDoc() || aDocument->IsStaticDocument() ||
      !aDocument->IsActive()) {
    return nullptr;
  }

  nsIDocShell* docShell = aDocument->GetDocShell();
  if (!docShell || docShell->IsInvisible()) {
    return nullptr;
  }

  nsIWidget* widget = nsContentUtils::WidgetForDocument(aDocument);
  if (!widget || widget->WindowType() == eWindowType_invisible) {
    return nullptr;
  }

  // Ignore documents without presshell and not having root frame.
  nsIPresShell* presShell = aDocument->GetShell();
  if (!presShell || presShell->IsDestroying())
    return nullptr;

  bool isRootDoc = nsCoreUtils::IsRootDocument(aDocument);

  DocAccessible* parentDocAcc = nullptr;
  if (!isRootDoc) {
    // XXXaaronl: ideally we would traverse the presshell chain. Since there's
    // no easy way to do that, we cheat and use the document hierarchy.
    parentDocAcc = GetDocAccessible(aDocument->GetParentDocument());
    NS_ASSERTION(parentDocAcc,
                 "Can't create an accessible for the document!");
    if (!parentDocAcc)
      return nullptr;
  }

  // We only create root accessibles for the true root, otherwise create a
  // doc accessible.
  RefPtr<DocAccessible> docAcc = isRootDoc ?
    new RootAccessibleWrap(aDocument, presShell) :
    new DocAccessibleWrap(aDocument, presShell);

  // Cache the document accessible into document cache.
  mDocAccessibleCache.Put(aDocument, docAcc);

  // Initialize the document accessible.
  docAcc->Init();

  // Bind the document to the tree.
  if (isRootDoc) {
    if (!ApplicationAcc()->AppendChild(docAcc)) {
      docAcc->Shutdown();
      return nullptr;
    }

    // Fire reorder event to notify new accessible document has been attached to
    // the tree. The reorder event is delivered after the document tree is
    // constructed because event processing and tree construction are done by
    // the same document.
    // Note: don't use AccReorderEvent to avoid coalsecense and special reorder
    // events processing.
    docAcc->FireDelayedEvent(nsIAccessibleEvent::EVENT_REORDER,
                             ApplicationAcc());

  } else {
    parentDocAcc->BindChildDocument(docAcc);
  }

#ifdef A11Y_LOG
  if (logging::IsEnabled(logging::eDocCreate)) {
    logging::DocCreate("document creation finished", aDocument);
    logging::Stack();
  }
#endif

  AddListeners(aDocument, isRootDoc);
  return docAcc;
}