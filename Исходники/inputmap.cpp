void ui_menu_input::handle()
{
	input_item_data *seqchangeditem = nullptr;
	const ui_menu_event *menu_event;
	int invalidate = false;

	/* process the menu */
	menu_event = process((pollingitem != nullptr) ? UI_MENU_PROCESS_NOKEYS : 0);

	/* if we are polling, handle as a special case */
	if (pollingitem != nullptr)
	{
		input_item_data *item = pollingitem;

		/* if UI_CANCEL is pressed, abort */
		if (ui_input_pressed(machine(), IPT_UI_CANCEL))
		{
			pollingitem = nullptr;
			record_next = false;
			toggle_none_default(item->seq, starting_seq, *item->defseq);
			seqchangeditem = item;
		}

		/* poll again; if finished, update the sequence */
		if (machine().input().seq_poll())
		{
			pollingitem = nullptr;
			record_next = true;
			item->seq = machine().input().seq_poll_final();
			seqchangeditem = item;
		}
	}

	/* otherwise, handle the events */
	else if (menu_event != nullptr && menu_event->itemref != nullptr)
	{
		input_item_data *item = (input_item_data *)menu_event->itemref;
		switch (menu_event->iptkey)
		{
			/* an item was selected: begin polling */
			case IPT_UI_SELECT:
				pollingitem = item;
				last_sortorder = item->sortorder;
				starting_seq = item->seq;
				machine().input().seq_poll_start((item->type == INPUT_TYPE_ANALOG) ? ITEM_CLASS_ABSOLUTE : ITEM_CLASS_SWITCH, record_next ? &item->seq : nullptr);
				invalidate = true;
				break;

			/* if the clear key was pressed, reset the selected item */
			case IPT_UI_CLEAR:
				toggle_none_default(item->seq, item->seq, *item->defseq);
				record_next = false;
				seqchangeditem = item;
				break;
		}

		/* if the selection changed, reset the "record next" flag */
		if (item->sortorder != last_sortorder)
			record_next = false;
		last_sortorder = item->sortorder;
	}

	/* if the sequence changed, update it */
	if (seqchangeditem != nullptr)
	{
		update_input(seqchangeditem);

		/* invalidate the menu to force an update */
		invalidate = true;
	}

	/* if the menu is invalidated, clear it now */
	if (invalidate)
	{
		pollingref = nullptr;
		if (pollingitem != nullptr)
		{
			pollingref = pollingitem->ref;
			pollingseq = pollingitem->seqtype;
		}
		reset(UI_MENU_RESET_REMEMBER_POSITION);
	}
}