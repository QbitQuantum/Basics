Epdf_Document *
epdf_document_new (const char *filename)
{
  Epdf_Document *doc;

  if (!filename)
    return NULL;

  doc = (Epdf_Document *)malloc (sizeof (Epdf_Document));
  if (!doc)
    return NULL;

  if (!globalParams)
    globalParams = new GlobalParams();

  doc->pdfdoc = new PDFDoc (new GooString (filename), NULL);
  if (doc->pdfdoc->isOk() || doc->pdfdoc->getErrorCode() == errEncrypted) {
    Object         obj;

    if (doc->pdfdoc->getErrorCode() == errEncrypted)
      doc->locked = true;
    else
      doc->locked = false;
    doc->scanner = new FontInfoScanner(doc->pdfdoc);

    doc->pdfdoc->getDocInfo (&obj);
    if (!obj.isDict ()) {
      obj.free ();
      free (doc);

      return NULL;
    }

    doc->dict = obj.getDict();

    return doc;
  }

  free (doc);

  return NULL;
}