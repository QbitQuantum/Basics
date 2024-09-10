int Cpdu::sendToLoadBalancer()
{
  int rc = 0;

  if (CLoadBalancer::Inst())
    rc = sendTo(CLoadBalancer::Inst()->getSocket());

  return rc;
}