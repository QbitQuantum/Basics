void NetLink::Recv(Frame *f)
{
	if(NULL != f->proc)
	{
		QueueUserWorkItem(NetLink_Recv, (LPVOID)f, WT_EXECUTEINIOTHREAD);
	}
	else
	{
		closesocket(f->socket);
		Frame::Drop(f);
	}
}