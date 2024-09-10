bool ProxyAccount::event(QEvent *ev)
{
	if (ev->type() == Event::eventType()) {
		Event *event = static_cast<Event*>(ev);
		static quint16 realAccountRequestEvent = Event::registerType("real-account-request");
		if (event->id == realAccountRequestEvent) {
			event->args[0] = qVariantFromValue<Account*>(m_account);
			event->accept();
			return true;
		}
	}
	return Account::event(ev);
}