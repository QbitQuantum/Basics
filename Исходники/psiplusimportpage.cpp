	void PsiPlusImportPage::SendImportAcc (QStandardItem *accItem)
	{
		Entity e = Util::MakeEntity (QVariant (),
				QString (),
				FromUserInitiated | OnlyHandle,
				"x-leechcraft/im-account-import");

		QVariantMap data = accItem->data (Roles::AccountData).toMap ();
		data.remove ("Contacts");
		e.Additional_ ["AccountData"] = data;

		emit gotEntity (e);
	}