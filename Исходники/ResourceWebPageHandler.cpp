bool ResourceWebPageHandler::handlePage(WebContext &ctx, ostream &stream,
                                        const URI &uri) {
  const Resource *res = root->find(uri.getPath());
  if (!res) return false;

  stream.write(res->getData(), res->getLength());

  return true;
}