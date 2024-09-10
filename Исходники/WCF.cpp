WCF::~WCF()
{
	if (proxy){
		WsCloseServiceProxy(proxy, NULL, NULL);
		WsFreeServiceProxy(proxy);
	}
	if (heap){ WsFreeHeap(heap); }
	if (error){ WsFreeError(error); }
}