/**
 * \brief Sends a notification to Growl.
 *
 * \param name the registered name of the notification.
 * \param title the title for the notification.
 * \param description the description of the notification.
 * \param icon the icon of the notification.
 * \param sticky whether the notification should be sticky (i.e. require a 
 *	click to discard.
 * \param receiver the receiving object which will be signaled when the
 *	notification is clicked. May be NULL.
 * \param slot the slot to be signaled when the notification is clicked.
 * \param context the context which will be passed back to the slot
 *	May be NULL.
 */
void GrowlNotifier::notify(const QString& name, const QString& title, 
	const QString& description, const QPixmap& p, bool sticky, 
	const QObject* receiver, 
	const char* clicked_slot, const char* timeout_slot, 
	void* qcontext)
{
	// Convert the image if necessary
	CFDataRef icon = 0;
	if (!p.isNull()) {
		QByteArray img_data;
		QBuffer buffer(&img_data);
		buffer.open(QIODevice::WriteOnly);
		p.save(&buffer, "PNG");
		icon = CFDataCreate( NULL, (UInt8*) img_data.data(), img_data.size());
	}

	// Convert strings
	CFStringRef cf_title = qString2CFString(title);
	CFStringRef cf_description = qString2CFString(description);
	CFStringRef cf_name = qString2CFString(name);

	// Do notification
	CFPropertyListRef context = createContext(signaler_, receiver, clicked_slot, timeout_slot, qcontext/*, getpid()*/);
	Growl_NotifyWithTitleDescriptionNameIconPriorityStickyClickContext(
		cf_title, cf_description, cf_name, icon, 0, sticky, context);
	
	// Release intermediary datastructures
	CFRelease(context);
	if (icon) 
		CFRelease(icon);
	if (cf_title) 
		CFRelease(cf_title);
	if (cf_description) 
		CFRelease(cf_description);
	if (cf_name) 
		CFRelease(cf_name);
}