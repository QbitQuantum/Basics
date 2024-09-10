void PhysicallyBased::run() {
	srand( time(NULL) );
	
	QTimer* timer = new QTimer(this);
	float timestepMS = theTime.timestep * 1000;
	timer->setInterval(timestepMS);
	timer->connect(timer, SIGNAL(timeout()), this, SLOT(simLoop()));
	timer->start();
	
	exec(); // start event loop
	
	//Application* mainApp = Application::getInstance();
	//QApplication::postEvent(mainApp, new QEvent(PhysBEvent::traceStart));
	//QApplication::postEvent(mainApp->SFMLView, new QEvent(PhysBEvent::tracePixelFilled));
	//QApplication::postEvent(eventManager, new QEvent(PhysBEvent::tracePixelFilled));
	//QApplication::postEvent(mainApp, new QEvent(PhysBEvent::traceEnd));
}