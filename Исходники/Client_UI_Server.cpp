/*
 * Handles a UI request to send a message to the Server
 * Sends the operation's result back to the UI client
 * @param sock - socket to the UI client
 * @param msgToSend - the message to be sent to the server
 */
void Client_UI_Server::handleRequestToSendMsgToServer (SocketWrapper& sock, string& msgToSend)
{
	string reply_to_ui_client, servers_reply;
	bool isBusted=false;

	//check that the message is within the max length limits:
	if (msgToSend.length() > g_maxMessageLength)
	{
		//we need to shorten the message:
		msgToSend = msgToSend.substr(0,g_maxMessageLength);
	}

	int resCode = m_clientMachine->UI_Callback_SendMsg(servers_reply,msgToSend);//send to Server

	//got the operation's result. send the appropriate answer to the UI client:
	switch (resCode)
	{
		case RET_VAL_TO_UI_SERVER_SERVER_SENT_UNKNOWN_REPLY:
		{
			//create a message:
			reply_to_ui_client = createMessage(UI_SERVER,
					 UI_CLIENT,
					 OPCODE_UI_SERVER_TO_CLIENT_SERVER_REPLY,
					 strlen(CONTENT_SERVER_SENT_UNKNOWN_REPLY),
					 CONTENT_SERVER_SENT_UNKNOWN_REPLY);
			break;
		}
		case RET_VAL_TO_UI_SERVER_SERVER_REPLY_OK:
		{
			//create a message:
			reply_to_ui_client = createMessage(UI_SERVER,
					 UI_CLIENT,
					 OPCODE_UI_SERVER_TO_CLIENT_SERVER_REPLY,
					 servers_reply.length(),
					 servers_reply);
			break;
		}
		case RET_VAL_TO_UI_SERVER_SERVER_DETECTED_VIRUS:
		{
			isBusted=true;
			cout << "The server has detected an attack and sent the following reply:" << endl \
					<< servers_reply;

			servers_reply += "\n The client program has terminated.\n Close this window before relaunching.\n";
			//create a message:
			reply_to_ui_client = createMessage(UI_SERVER,
					 UI_CLIENT,
					 OPCODE_UI_SERVER_TO_CLIENT_SERVER_REPLY,
					 servers_reply.length(),
					 servers_reply);
			break;
		}
		case RET_VAL_TO_UI_SERVER_FAILED_TO_OPEN_A_SOCKET:
		{
			cout << "Failed to open a socket!" << endl;
			//create a message:
			reply_to_ui_client = createMessage(UI_SERVER,
					 UI_CLIENT,
					 OPCODE_UI_SERVER_TO_CLIENT_SOCKET_OPEN_FAILED,
					 strlen(CONTENT_SOCKET_OPEN_FAILED),
					 CONTENT_SOCKET_OPEN_FAILED);
			break;
		}

	}//switch


	sock.sendToSocket(reply_to_ui_client.c_str(), reply_to_ui_client.length()); //send the reply
	sock.closeSocket();

	if (isBusted)
		Quit(1);

}//end of handleRequestToSendMsgToServer()