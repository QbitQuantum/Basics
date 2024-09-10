Server_ProtocolHandler::Server_ProtocolHandler(Server *_server, QObject *parent)
	: QObject(parent), server(_server), authState(PasswordWrong), acceptsUserListChanges(false), acceptsRoomListChanges(false), userInfo(0), lastCommandTime(QDateTime::currentDateTime())
{
	connect(server, SIGNAL(pingClockTimeout()), this, SLOT(pingClockTimeout()));
}