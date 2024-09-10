void EntityApp<E>::onExecScriptCommand(Mercury::Channel* pChannel, std::string& strcommand)
{
	DEBUG_MSG("EntityApp::onExecScriptCommand: command size(%d).\n", strcommand.size());

	std::string retbuf = "";
	if(script_.run_simpleString(strcommand, &retbuf) == 0)
	{
		// 将结果返回给客户端
		Mercury::Bundle bundle;
		ConsoleInterface::ConsoleExecCommandCBMessageHandler msgHandler;
		bundle.newMessage(msgHandler);
		ConsoleInterface::ConsoleExecCommandCBMessageHandlerArgs1::staticAddToBundle(bundle, retbuf);
		bundle.send(this->getNetworkInterface(), pChannel);
	}
}