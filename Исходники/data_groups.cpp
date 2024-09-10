void Groups::refreshMessage(not_null<HistoryItem*> item) {
	if (!isGrouped(item)) {
		unregisterMessage(item);
		return;
	}
	if (!IsServerMsgId(item->id)) {
		return;
	}
	const auto groupId = item->groupId();
	const auto i = _groups.find(groupId);
	if (i == end(_groups)) {
		registerMessage(item);
		return;
	}
	auto &items = i->second.items;
	const auto position = findPositionForItem(items, item);
	auto current = ranges::find(items, item);
	if (current == end(items)) {
		items.insert(position, item);
	} else if (position == current + 1) {
		return;
	} else if (position > current + 1) {
		for (++current; current != position; ++current) {
			std::swap(*(current - 1), *current);
		}
	} else if (position < current) {
		for (; current != position; --current) {
			std::swap(*(current - 1), *current);
		}
	} else {
		Unexpected("Position of item in Groups::refreshMessage().");
	}
	refreshViews(items);
}