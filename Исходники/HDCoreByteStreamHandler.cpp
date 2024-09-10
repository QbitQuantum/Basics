HRESULT HDCoreByteStreamHandler::Invoke(IMFAsyncResult* pAsyncResult)
{
	std::lock_guard<decltype(_mutex)> lock(_mutex);

	if (_mediaSource == nullptr)
		return E_UNEXPECTED;

	_openResult->SetStatus(pAsyncResult->GetStatus());
	return MFInvokeCallback(_openResult.Get()); //Notify to System...
}