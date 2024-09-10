//Handle all messages in the queue
VOID WindowMessageDispatcher12::RunMessagePump() {
	MSG Message;

	while (PeekMessageW(&Message, m_Handle, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&Message);
		DispatchMessageW(&Message);
	}
}