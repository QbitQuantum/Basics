void paintImportantSwitch(Painter &p, Mode current, int fullWidth, bool selected, bool onlyBackground) {
	p.fillRect(0, 0, fullWidth, st::dialogsImportantBarHeight, selected ? st::dialogsBgOver : st::dialogsBg);
	if (onlyBackground) {
		return;
	}

	p.setFont(st::semiboldFont);
	p.setPen(st::dialogsNameFg);

	int unreadTop = (st::dialogsImportantBarHeight - st::dialogsUnreadHeight) / 2;
	bool mutedHidden = (current == Dialogs::Mode::Important);
	QString text = lang(mutedHidden ? lng_dialogs_show_all_chats : lng_dialogs_hide_muted_chats);
	int textBaseline = unreadTop + (st::dialogsUnreadHeight - st::dialogsUnreadFont->height) / 2 + st::dialogsUnreadFont->ascent;
	p.drawText(st::dialogsPadding.x(), textBaseline, text);

	if (mutedHidden) {
		if (int32 unread = App::histories().unreadMutedCount()) {
			int unreadRight = fullWidth - st::dialogsPadding.x();
			UnreadBadgeStyle st;
			st.muted = true;
			paintUnreadCount(p, QString::number(unread), unreadRight, unreadTop, st, nullptr);
		}
	}
}