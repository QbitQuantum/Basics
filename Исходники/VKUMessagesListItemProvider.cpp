TableViewItem* VKUMessagesListItemProvider::CreateItem(int index, int itemWidth) {
	result r;
	AppLog("VKUMessagesListItemProvider::CreateItem");

	RoundedAvatar *pAvatar; // NOTE: used only if chat and message is out==0
	MessageBubble* pMessageBubble;
	RelativeLayout itemLayout;
	Color bgColor;

	JsonObject *itemObject;
	IJsonValue *itemValue;
	TableViewItem* pItem;
	JsonNumber outNumber;

	ArrayList *pMessageElements;

	Label *pTimeStamp;
	String timespampText;
	int timestampValue;

	String messageText(L"no text????");
	int out = 0, readState = 0;

	// reverse list
	int reversedIndex = _messagesJson->GetCount() - 1 - index;
	AppLog("Item %d of %d", reversedIndex, GetItemCount());

	// get message string
	r = _messagesJson->GetAt(reversedIndex, itemValue);
	TryCatch(r == E_SUCCESS, , "Failed GetAt");
	itemObject = static_cast<JsonObject *>(itemValue);

	JsonParseUtils::GetInteger(*itemObject, L"out", out);
	JsonParseUtils::GetInteger(*itemObject, L"date", timestampValue);
	JsonParseUtils::GetInteger(*itemObject, L"read_state", readState);

	TimeUtils::GetDialogsTime(timestampValue, timespampText);

	// create rich text panel
	AppLog("Message is %d == out", out);
	pMessageBubble = new MessageBubble();
	r = pMessageBubble->Construct(Dimension(itemWidth, LIST_HEIGHT));
	TryCatch(r == E_SUCCESS, , "Failed Construct RichTextPanel");

	pMessageBubble->SetOut(out);
	AppLog("RTPanel created and constructed");
	itemLayout.Construct();

	// get available elements
	pMessageElements = GetMessageElementsN(itemObject, itemWidth);

	// message text element
	for (int i=0; i<pMessageElements->GetCount(); i++) {
		AppLog("Adding element %d to pItem", i);
		MessageElement *pElement = static_cast<MessageElement *>(pMessageElements->GetAt(i));
		pMessageBubble->AddElement(pElement);
		AppLog("Added element %d to pItem with size of %dx%d", i, pElement->GetWidth(), pElement->GetHeight());
	}

	// timestamp label
	pTimeStamp = new Label();
	pTimeStamp->Construct(Rectangle(0, 0, 100, 28), timespampText);
	pTimeStamp->SetTextConfig(28, LABEL_TEXT_STYLE_NORMAL);
	pTimeStamp->SetTextColor(Color(TIMESTAMP_TEXT_COLOR, false));

	// create table item
	pItem = new TableViewItem();
	r = pItem->Construct(itemLayout, Dimension(itemWidth, pMessageBubble->GetHeight() + 2*BUBBLE_VERTICAL_MARGIN));
	TryCatch(r == E_SUCCESS, , "Failed GetAt");

	if (out == 0 && _peerId > 2000000000) {
		int fromId;
		JsonParseUtils::GetInteger(*itemObject, L"from_id", fromId);
		AppLog("Finding avatar for %d", fromId);

		pAvatar = new RoundedAvatar(AVATAR_NORMAL);
		String * avatarUrl = static_cast<String *>(_pUserIdAvatarMap->GetValue(Integer(fromId)));

		pAvatar->Construct(Rectangle(0, 0, 80, 80), *avatarUrl);
		r = pItem->AddControl(pAvatar);
		itemLayout.SetRelation(*pAvatar, pItem, RECT_EDGE_RELATION_LEFT_TO_LEFT);
		itemLayout.SetRelation(*pAvatar, pItem, RECT_EDGE_RELATION_TOP_TO_TOP);
		itemLayout.SetMargin(*pAvatar, 10, 0, 10, 0);
	}

	// add rich text panel to table item
	r = pItem->AddControl(pMessageBubble);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");
	r = pItem->AddControl(pTimeStamp);

	itemLayout.SetCenterAligned(*pMessageBubble, CENTER_ALIGN_VERTICAL);
	itemLayout.SetHorizontalFitPolicy(*pTimeStamp, FIT_POLICY_CONTENT);

	if (out == 1) {
		itemLayout.SetRelation(*pMessageBubble, *pItem, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
		itemLayout.SetMargin(*pMessageBubble, 0, 10, 0, 0);

		itemLayout.SetRelation(*pTimeStamp, *pMessageBubble, RECT_EDGE_RELATION_RIGHT_TO_LEFT);
		itemLayout.SetRelation(*pTimeStamp, *pItem, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
		itemLayout.SetMargin(*pTimeStamp, 0, 10, 0, 30);
	} else {
		if (_peerId > 2000000000) {
			itemLayout.SetRelation(*pMessageBubble, pAvatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
			itemLayout.SetMargin(*pMessageBubble, 10, 0, 0, 0);
		} else {
			itemLayout.SetRelation(*pMessageBubble, *pItem, RECT_EDGE_RELATION_LEFT_TO_LEFT);
			itemLayout.SetMargin(*pMessageBubble, 10, 0, 0, 0);
		}

		itemLayout.SetRelation(*pTimeStamp, *pMessageBubble, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
		itemLayout.SetRelation(*pTimeStamp, *pItem, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
		itemLayout.SetMargin(*pTimeStamp, 10, 0, 0, 30);
	}

	// colors
	if (out == 1 && readState == 0) {
		bgColor = Color(LIST_ITEM_UNREAD_COLOR, false);
	} else {
		bgColor = Color::GetColor(COLOR_ID_BLACK);
	}

	pItem->SetBackgroundColor(bgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_NORMAL);
	pItem->SetBackgroundColor(bgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_PRESSED);
	pItem->SetBackgroundColor(bgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_HIGHLIGHTED);

	pItem->RequestRedraw(true);

	AppLog("Returning item");
	return pItem;

CATCH:
	AppLogException("$${Function:CreateItem} is failed. %s", GetErrorMessage(r));
	return null;
}