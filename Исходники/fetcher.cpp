Future<Nothing> Fetcher::fetch(
    const URI& uri,
    const string& directory) const
{
  if (!plugins.contains(uri.scheme())) {
    return Failure("Scheme '" + uri.scheme() + "' is not supported");
  }

  return plugins.at(uri.scheme())->fetch(uri, directory);
}