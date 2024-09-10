bool ProxyContact::eventFilter(QObject *obj, QEvent *ev)
{
	if (obj == m_conf.data() && ev->type() == Event::eventType()) {
		Event *event = static_cast<Event*>(ev);
		static quint16 realUnitRequestEvent = Event::registerType("real-chatunit-request");
		if (event->id == realUnitRequestEvent) {
			event->args[0] = qVariantFromValue<Contact*>(this);
			event->accept();
			return true;
		}
	}
	return Contact::eventFilter(obj, ev);
}