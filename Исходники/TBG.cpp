http::Response * Server::wait(QFuture<http::Response *> future) {
	
	QEventLoop loop;
	
	// Interrrupt the event loop when the result is available
	QFutureWatcher<http::Response *> watcher;
	watcher.setFuture(future);
	loop.connect(&watcher, SIGNAL(finished()), SLOT(quit()));
	
	// Prevent infinite loop if the future completes before we start the loop
	QTimer timer;
	loop.connect(&timer, SIGNAL(timeout()), SLOT(quit()));
	timer.setSingleShot(false);
	timer.start(1000);
	
	// Process events while waiting so that the UI stays responsive
	while(!future.isFinished()) {
		loop.exec();
	}
	
	http::Response * response = future.result();
	
	if(response->ok()) {
		m_lastErrorString.clear();
	} else if(!response->error().empty()) {
		m_lastErrorString = toQString(response->error());
	} else if(!response->data().empty()) {
		m_lastErrorString = toQString(response->data());
	} else {
		m_lastErrorString = "HTTP Error " + QString::number(response->status());
	}
	
	return response;
}