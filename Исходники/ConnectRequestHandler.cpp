ConnectRequestHandler::ConnectRequestHandler(const ReferencePtr& ref, 
                                             const Ice::ObjectPrx& proxy,
                                             const Handle< ::IceDelegate::Ice::Object>& delegate) :
    RequestHandler(ref),
    _proxy(proxy),
    _delegate(delegate),
    _batchAutoFlush(
        ref->getInstance()->initializationData().properties->getPropertyAsIntWithDefault("Ice.BatchAutoFlush", 1) > 0),
    _initialized(false),
    _flushing(false),
    _batchRequestInProgress(false),
    _batchRequestsSize(sizeof(requestBatchHdr)),
    _batchStream(ref->getInstance().get(), Ice::currentProtocolEncoding, _batchAutoFlush),
    _updateRequestHandler(false)
{
}