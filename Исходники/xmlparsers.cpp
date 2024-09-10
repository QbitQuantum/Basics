	RepoInfo ParseRepoInfo (const QUrl& url, const QString& data)
	{
		QXmlQuery query;
		query.setFocus (data);

		RepoInfo info (url);

		QString out;
		query.setQuery ("/repo/name/text()");
		if (!query.evaluateTo (&out))
			throw QObject::tr ("Could not get repo name.");
		info.SetName (out.simplified ());

		query.setQuery ("/repo/description/short/text()");
		if (!query.evaluateTo (&out))
			throw QObject::tr ("Could not get repo description.");
		info.SetShortDescr (out.simplified ());

		query.setQuery ("/repo/description/long/text()");
		if (!query.evaluateTo (&out))
			throw QObject::tr ("Could not get long repo description.");
		info.SetLongDescr (out.simplified ());

		MaintainerInfo maintInfo;
		query.setQuery ("/repo/maintainer/name/text()");
		if (!query.evaluateTo (&out))
			throw QObject::tr ("Could not get maintainer name.");
		maintInfo.Name_ = out.simplified ();

		query.setQuery ("/repo/maintainer/email/text()");
		if (!query.evaluateTo (&out))
			throw QObject::tr ("Could not get maintainer email.");
		maintInfo.Email_ = out.simplified ();

		info.SetMaintainer (maintInfo);

		QStringList components;
		query.setQuery ("/repo/components/component/text()");
		if (query.evaluateTo (&components))
			info.SetComponents (components);
		else if (query.evaluateTo (&out))
			info.SetComponents (QStringList (out));
		else
			throw QObject::tr ("Could not get components.");

		return info;
	}