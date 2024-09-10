Fiber::Fiber() {
	m_fiber = CreateFiber(0, Fiber::fiberStartingFunction, this);
	m_isThread = false;
}