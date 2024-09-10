void GDNetHost::thread_loop() {
	while (_running) {
		acquireMutex();

		send_messages();
		poll_events();

		releaseMutex();
	}
}