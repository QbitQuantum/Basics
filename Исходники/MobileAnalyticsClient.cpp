PutEventsOutcome MobileAnalyticsClient::PutEvents(const PutEventsRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/2014-06-05/events";
 uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return PutEventsOutcome(NoResult());
  }
  else
  {
    return PutEventsOutcome(outcome.GetError());
  }
}