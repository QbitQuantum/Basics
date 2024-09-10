// Handle messages to the main view
void
OutputFormatView::MessageReceived(BMessage *msg)
{
	int32 item_index;
	const char *info_lines[3];

	switch (msg->what)
	{
		case ITEM_SELECTED:
			if (msg->FindInt32("index", &item_index) == B_OK &&
			    item_index >= 0 &&
			    item_index < list_view->CountItems())
			{
				// Store the currently selected item
				// in the class member 'index'
				index = item_index;
				// Update the info view and config view
				int32 outVersion;
				the_roster->GetTranslatorInfo(
					output_list[item_index].translator,
					&name_line,
					&info_line,
					&outVersion);
				int32 ver = outVersion / 100;
				int32 rev1 = (outVersion % 100) / 10;
				int32 rev2 = outVersion % 10;
				sprintf(version_line, "Version %ld.%ld.%ld", ver, rev1, rev2);
				info_lines[0] = name_line;
				info_lines[1] = info_line;
				info_lines[2] = version_line;
				info_view->SetInfoLines(info_lines);
				AddConfigView();
			}
			else
			{
				// Reselect the original item
				if (index >= 0)
					list_view->Select(index);
			}
			break;

		case INVOKE_LIST:
		{
			// The main button was pressed
			// Find out which item is selected, and invoke it
			int32 item_count = list_view->CountItems();
			for (int32 i = 0; i < item_count; ++i)
			{
				if (list_view->IsItemSelected(i))
				{
					list_view->Invoke();
					break;
				}
			}
			break;
		}
		case SEND_MESSAGE:
			// An output format has been selected
			if (!message_sent &&
			    msg->FindInt32("index", &item_index) == B_OK &&
			    item_index >= 0 &&
			    item_index < list_view->CountItems())
			{
				// Get the message from the invoker
				BMessage *the_message=selected_invoker->Message();
				

				// Add some info about the selected output format to it
				the_message->AddInt32("translator", output_list[item_index].translator);
				the_message->AddInt32("type", output_list[item_index].type);

				// Send the message
				selected_invoker->Invoke(the_message);
				message_sent = true;
				the_window->PostMessage(MESSAGE_SENT);
			}
			break;

		default:
			BView::MessageReceived(msg);
			break;
	}
}