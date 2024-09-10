void QuetzalAccount::timerEvent(QTimerEvent *ev)
{
	if (m_chatTimer.timerId() != ev->timerId())
		return Account::timerEvent(ev);
	m_chatTimer.stop();
	Config cfg = config();
	cfg.remove(QLatin1String("chats"));
	cfg.beginArray(QLatin1String("chats"));
	GList *chats = quetzal_blist_get_chats(m_account);
	int i = 0;
	QString name = QLatin1String("name");
	QString recent = QLatin1String("recent");
	QString data = QLatin1String("data");
	for (GList *it = chats; it; it = it->next, i++) {
		cfg.setArrayIndex(i);
		PurpleChat *chat = PURPLE_CHAT(it->data);
		cfg.setValue(name, QString::fromUtf8(chat->alias));
		cfg.setValue(recent, !qstrcmp(purple_group_get_name(purple_chat_get_group(chat)), "Recent"));
		cfg.beginGroup(data);
		g_hash_table_foreach(chat->components, (GHFunc)quetzal_save_chat, &cfg);
		cfg.endGroup();
	}
	g_list_free(chats);
}