QVariantMap authActionQueryPerms(int i, QIODevice *connection,
	const QSqlDatabase& db, const QSqlDatabase& user_db,
	const QVariantMap& action, const QString& email)
{
	Q_UNUSED(i);
	Q_UNUSED(db);
	Q_UNUSED(user_db);
	Q_UNUSED(connection);

	if( action.contains("email") )
	{
		QVariantMap perms = auth->queryPerms(
			action.value("email").toString() ).toMap();
		perms.remove("any");

		QVariantMap map;
		map["email"] = action.value("email");
		map["perms"] = perms;

		return map;
	}
	else
	{
		QVariantMap perms = auth->queryPerms(email).toMap();
		perms.remove("any");

		QVariantMap map;
		map["email"] = email;
		map["perms"] = perms;

		return map;
	}
}