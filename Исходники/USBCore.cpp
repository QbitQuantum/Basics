//	Does not timeout or cross fifo boundaries
int USB_RecvControl(void* d, int len)
{
	auto length = len;
	while(length)
	{
		// Dont receive more than the USB Control EP has to offer
		// Use fixed 64 because control EP always have 64 bytes even on 16u2.
		auto recvLength = length;
		if(recvLength > 64){
			recvLength = 64;
		}

		// Write data to fit to the end (not the beginning) of the array
		WaitOUT();
		Recv((u8*)d + len - length, recvLength);
		ClearOUT();
		length -= recvLength;
	}
	return len;
}