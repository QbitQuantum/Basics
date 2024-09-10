INT_PTR NetlibShutdown(WPARAM wParam, LPARAM)
{
	if (wParam) 
	{
		WaitForSingleObject(hConnectionHeaderMutex,INFINITE);
		switch(GetNetlibHandleType(wParam)) {
			case NLH_CONNECTION:
				{
					struct NetlibConnection* nlc = (struct NetlibConnection*)wParam;
					if (nlc->hSsl) si.shutdown(nlc->hSsl);
					if (nlc->s != INVALID_SOCKET) shutdown(nlc->s, 2);
					if (nlc->s2 != INVALID_SOCKET) shutdown(nlc->s2, 2);
					nlc->termRequested = true;
				}
				break;
			case NLH_BOUNDPORT:
				{
					struct NetlibBoundPort* nlb = (struct NetlibBoundPort*)wParam;
					if (nlb->s != INVALID_SOCKET) shutdown(nlb->s, 2);
				}
				break;
		}
		ReleaseMutex(hConnectionHeaderMutex);

	}
	return 0;
}