CheckDomainAvailabilityOutcome Route53DomainsClient::CheckDomainAvailability(const CheckDomainAvailabilityRequest& request) const
{
  Aws::StringStream ss;
  Aws::Http::URI uri = m_uri;
  ss << "/";
 uri.SetPath(uri.GetPath() + ss.str());
  JsonOutcome outcome = MakeRequest(uri, request, HttpMethod::HTTP_POST);
  if(outcome.IsSuccess())
  {
    return CheckDomainAvailabilityOutcome(CheckDomainAvailabilityResult(outcome.GetResult()));
  }
  else
  {
    return CheckDomainAvailabilityOutcome(outcome.GetError());
  }
}