int
MLQuery::queryNewWorkOrders()
{
  MLogClient logClient;

  logClient.log(MLogClient::MLOG_VERBOSE,
                "",
                "MLQuery::queryAllWorkOrders",
                __LINE__,
                "Poll for all work orders");

  MWorkOrderVector::iterator pStart = mWorkOrderVector.begin();
  MWorkOrderVector::iterator pEnd   = mWorkOrderVector.end();
  mWorkOrderVector.erase(pStart, pEnd);

  mImageManager.queryWorkOrder(*this, 0);

  return 0;
}