void HTTPServerResponseImpl::sendContinue()
{
	HTTPHeaderOutputStream hs(_session);
	hs << getVersion() << " 100 Continue\r\n\r\n";
}