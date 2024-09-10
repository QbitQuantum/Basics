ReusableThread& ReusableThread::operator=(ReusableThread&& obj) {
	lock_guard<mutex> memberGuard(this->memberMutex);
	lock_guard<mutex> objMemberGuard(obj.memberMutex);
	if (this->t->joinable()) {
		terminate();
	}

	std::swap(this->helper, obj.helper);
	std::swap(this->t, obj.t);

	return *this;
}