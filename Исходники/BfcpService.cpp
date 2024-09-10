void BfcpService::handleGetConferenceInfoResult(std::string &info, 
                                                bfcp::ControlError error, 
                                                void *data)
{
  muduo::MutexLockGuard lock(mutex_);
  error_ = error;
  callFinished_ = true;
  if (data)
  {
    bfcp::string *res = static_cast<bfcp::string*>(data);
    info.swap(*res);
  }
  cond_.notify();
}