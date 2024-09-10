void
LookAndFeelSettingsView::MessageReceived(BMessage *msg)
{
	switch (msg->what) {
		case kMsgSetDecor:
		{
			BString newDecor;
			if (msg->FindString("decor", &newDecor) == B_OK)
				_SetDecor(newDecor);
			break;
		}

		case kMsgDecorInfo:
		{
			DecorInfo* decor = fDecorUtility.FindDecorator(fCurrentDecor);
			if (decor == NULL)
				break;

			BString authorsText(decor->Authors().String());
			authorsText.ReplaceAll(", ", "\n\t");

			BString infoText(B_TRANSLATE("%decorName\n\n"
				"Authors:\n\t%decorAuthors\n\n"
				"URL: %decorURL\n"
				"License: %decorLic\n\n"
				"%decorDesc\n"));


			infoText.ReplaceFirst("%decorName", decor->Name().String());
			infoText.ReplaceFirst("%decorAuthors", authorsText.String());
			infoText.ReplaceFirst("%decorLic", decor->LicenseName().String());
			infoText.ReplaceFirst("%decorURL", decor->SupportURL().String());
			infoText.ReplaceFirst("%decorDesc", decor->ShortDescription().String());

			BAlert *infoAlert = new BAlert(B_TRANSLATE("About decorator"),
				infoText.String(), B_TRANSLATE("OK"));
			infoAlert->SetFlags(infoAlert->Flags() | B_CLOSE_ON_ESCAPE);
			infoAlert->Go();

			break;
		}

		case kMsgArrowStyleSingle:
			_SetDoubleScrollBarArrows(false);
			break;

		case kMsgArrowStyleDouble:
			_SetDoubleScrollBarArrows(true);
			break;

		default:
			BView::MessageReceived(msg);
			break;
	}
}