static void HTTPProxy_OutputFrom_InputTo(HTTPProxy *proxy)
{
	AMessage *msg = proxy->openmsg;
	proxy->openmsg = NULL;

	aobject_addref(&proxy->object);
	QueueUserWorkItem(HTTPProxy_OutputTo_InputFrom, &proxy->object, 0);

	amsg_init(&proxy->inmsg, AMsgType_Unknown, proxy->indata, sizeof(proxy->indata));
	amsg_copy(&proxy->inmsg, msg->type, msg->data, msg->size);

	proxy->inmsg.data[proxy->inmsg.size] = '\0';
	OutputDebugStringA(proxy->inmsg.data);

	aobject_addref(&proxy->object);
	HTTPProxyOutputFrom(&proxy->inmsg, 1);
}