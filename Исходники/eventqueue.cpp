void EventQueue::run() {
	QEventLoop loop;
	loop.connect(this, SIGNAL(_stop()), SLOT(quit()));
	Task bgTask;
	this->_bgTask = &bgTask;
	this->_bgTask->setMouseArea(this->_view);
	emit this->_started();
	loop.exec();
	this->_bgTask = nullptr;
	emit this->_stopped();
}