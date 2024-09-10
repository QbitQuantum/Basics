void
DialUpView::MessageReceived(BMessage *message)
{
	switch(message->what) {
		case PPP_REPORT_MESSAGE:
			HandleReportMessage(message);
		break;
		
		// -------------------------------------------------
		case kMsgCreateNew: {
			(new TextRequestDialog(kLabelCreateNewInterface, kTextChooseInterfaceName,
					kLabelInterfaceName))->Go(
				new BInvoker(new BMessage(kMsgFinishCreateNew), this));
		} break;
		
		case kMsgFinishCreateNew: {
			int32 which;
			message->FindInt32("which", &which);
			const char *name = message->FindString("text");
			if(which == 1 && name && strlen(name) > 0)
				AddInterface(name, true);
			
			if(fCurrentItem)
				fCurrentItem->SetMarked(true);
		} break;
		// -------------------------------------------------
		
		case kMsgDeleteCurrent: {
			if(!fCurrentItem)
				return;
			
			fInterfaceMenu->RemoveItem(fCurrentItem);
			BDirectory settings, profile;
			GetPPPDirectories(&settings, &profile);
			BEntry entry;
			settings.FindEntry(fCurrentItem->Label(), &entry);
			entry.Remove();
			profile.FindEntry(fCurrentItem->Label(), &entry);
			entry.Remove();
			delete fCurrentItem;
			fCurrentItem = NULL;
			
			BMenuItem *marked = fInterfaceMenu->FindMarked();
			if(marked)
				marked->SetMarked(false);
			
			UpdateControls();
			SelectInterface(0);
				// this stops watching the deleted interface
		} break;
		
		case kMsgSelectInterface: {
			int32 index;
			message->FindInt32("index", &index);
			SelectInterface(index);
		} break;
		
		case kMsgConnectButton: {
			if(!fCurrentItem || fUpDownThread != -1)
				return;
			
			fUpDownThread = spawn_thread(up_down_thread, "up_down_thread",
				B_NORMAL_PRIORITY, this);
			resume_thread(fUpDownThread);
		} break;
		
		default:
			BView::MessageReceived(message);
	}
}