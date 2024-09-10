void MembersBox::Inner::paintDialog(Painter &p, TimeMs ms, PeerData *peer, MemberData *data, bool selected, bool kickSelected) {
	UserData *user = peer->asUser();

	p.fillRect(0, 0, width(), _rowHeight, selected ? st::contactsBgOver : st::contactsBg);
	if (data->ripple) {
		data->ripple->paint(p, 0, 0, width(), ms);
		if (data->ripple->empty()) {
			data->ripple.reset();
		}
	}
	peer->paintUserpicLeft(p, st::contactsPadding.left(), st::contactsPadding.top(), width(), st::contactsPhotoSize);

	p.setPen(st::contactsNameFg);

	int32 namex = st::contactsPadding.left() + st::contactsPhotoSize + st::contactsPadding.left();
	int32 namew = width() - namex - st::contactsPadding.right() - (data->canKick ? (_kickWidth + st::contactsCheckPosition.x() * 2) : 0);
	if (peer->isVerified()) {
		auto icon = &st::dialogsVerifiedIcon;
		namew -= icon->width();
		icon->paint(p, namex + qMin(data->name.maxWidth(), namew), st::contactsPadding.top() + st::contactsNameTop, width());
	}
	data->name.drawLeftElided(p, namex, st::contactsPadding.top() + st::contactsNameTop, namew, width());

	if (data->canKick) {
		p.setFont(kickSelected ? st::linkOverFont : st::linkFont);
		p.setPen(kickSelected ? st::defaultLinkButton.overColor : st::defaultLinkButton.color);
		p.drawTextRight(st::contactsPadding.right() + st::contactsCheckPosition.x(), st::contactsPadding.top() + (st::contactsPhotoSize - st::normalFont->height) / 2, width(), _kickText, _kickWidth);
	}

	p.setFont(st::contactsStatusFont->f);
	p.setPen(data->onlineColor ? st::contactsStatusFgOnline : (selected ? st::contactsStatusFgOver : st::contactsStatusFg));
	p.drawTextLeft(namex, st::contactsPadding.top() + st::contactsStatusTop, width(), data->online);
}