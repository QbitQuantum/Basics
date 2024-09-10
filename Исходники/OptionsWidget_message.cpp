void OptionsWidget_messageColors::save()
{
	QString szName;
	QString szInit;
	g_pApp->getLocalKvircDirectory(szInit,KviApplication::MsgColors);

	if(KviFileDialog::askForSaveFileName(szName,__tr2qs_ctx("Choose a Filename - KVIrc","options"),szInit))
	{
		if(m_pLastItem)saveLastItem();

		KviConfigurationFile cfg(szName,KviConfigurationFile::Write);

		cfg.setGroup("Messages");

		KviCString tmp;


		int count = m_pListView->count();
		for(int i=0; i<count;i++)
		{
			MessageListWidgetItem* it = (MessageListWidgetItem *)m_pListView->item(i);

			tmp.sprintf("Fore%d",it->optionId());
			cfg.writeEntry(tmp.ptr(),it->msgType()->fore());
			tmp.sprintf("Back%d",it->optionId());
			cfg.writeEntry(tmp.ptr(),it->msgType()->back());
			tmp.sprintf("Icon%d",it->optionId());
			cfg.writeEntry(tmp.ptr(),it->msgType()->pixId());
			tmp.sprintf("Log%d",it->optionId());
			cfg.writeEntry(tmp.ptr(),it->msgType()->logEnabled());
			tmp.sprintf("Level%d",it->optionId());
			cfg.writeEntry(tmp.ptr(),it->msgType()->level());
		}

	}
}