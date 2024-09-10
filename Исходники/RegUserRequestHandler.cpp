	RequestReplyPointer RegUserRequestHandler::handle(Server* server, RequestHandlerArguments arguments)
	{
		// At least one argument (user uid) must exist.
		if (!arguments.size())
			throw "Uid is required for register user.";

		// Uid of user must be correct.
		UserIdentifier uid = arguments.front();
		if (!User::checkUid(uid))
			throw "Uid of user is incorrect.";

		// Register user with specified uid.
		RequestReply* reply;
		User* user = new User(uid);
		if (server->registerUser(user))
			reply = new RequestReply(user->getToken(), OK);
		else
			reply = new RequestReply(ERROR);
		delete user;
		return reply;

	} // End