void FilterUtility::CheckPermission(const ApiUser::Ptr& user, const String& permission, Expression **permissionFilter)
{
	if (permissionFilter)
		*permissionFilter = NULL;

	if (permission.IsEmpty())
		return;

	bool foundPermission = false;
	String requiredPermission = permission.ToLower();

	Array::Ptr permissions = user->GetPermissions();
	if (permissions) {
		ObjectLock olock(permissions);
		BOOST_FOREACH(const Value& item, permissions) {
			String permission;
			Function::Ptr filter;
			if (item.IsObjectType<Dictionary>()) {
				Dictionary::Ptr dict = item;
				permission = dict->Get("permission");
				filter = dict->Get("filter");
			} else
				permission = item;

			permission = permission.ToLower();

			if (!Utility::Match(permission, requiredPermission))
				continue;

			foundPermission = true;

			if (filter && permissionFilter) {
				std::vector<Expression *> args;
				args.push_back(new GetScopeExpression(ScopeLocal));
				FunctionCallExpression *fexpr = new FunctionCallExpression(new IndexerExpression(MakeLiteral(filter), MakeLiteral("call")), args);

				if (!*permissionFilter)
					*permissionFilter = fexpr;
				else
					*permissionFilter = new LogicalOrExpression(*permissionFilter, fexpr);
			}
		}
	}