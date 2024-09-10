	bool FotoBilderAccount::IsErrorReply (const QByteArray& content)
	{
		QXmlQuery query;
		query.setFocus (content);

		QString code;
		query.setQuery ("/FBResponse/Error/@code/data(.)");
		if (!query.evaluateTo (&code))
		{
			query.setQuery ("/FBResponse/CreateGalsResponse/Error/@code/data(.)");
			if (!query.evaluateTo (&code))
				return false;
		}
		code = code.simplified ();

		QString string;
		query.setQuery ("/FBResponse/Error/text()");
		if (!query.evaluateTo (&string))
		{
			query.setQuery ("/FBResponse/CreateGalsResponse/Error/text()");
			if (!query.evaluateTo (&string))
				return false;
		}
		string = string.simplified ();

		if (code.isEmpty () || string.isEmpty ())
			return false;

		Proxy_->GetEntityManager ()->HandleEntity (Util::MakeNotification ("Blasq DeathNote",
				tr ("%1 (original message: %2)")
						.arg (LocalizedErrorFromCode (code.toInt ()))
						.arg (string),
				Priority::PWarning_));

		return true;
	}