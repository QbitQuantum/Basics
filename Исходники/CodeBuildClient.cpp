ListCuratedEnvironmentImagesOutcome CodeBuildClient::ListCuratedEnvironmentImages(const ListCuratedEnvironmentImagesRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/";
 uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return ListCuratedEnvironmentImagesOutcome(ListCuratedEnvironmentImagesResult(outcome.GetResult()));
  }
  else
  {
    return ListCuratedEnvironmentImagesOutcome(outcome.GetError());
  }
}