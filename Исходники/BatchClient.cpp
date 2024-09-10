UpdateJobQueueOutcome BatchClient::UpdateJobQueue(const UpdateJobQueueRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/v1/updatejobqueue";
 uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return UpdateJobQueueOutcome(UpdateJobQueueResult(outcome.GetResult()));
  }
  else
  {
    return UpdateJobQueueOutcome(outcome.GetError());
  }
}