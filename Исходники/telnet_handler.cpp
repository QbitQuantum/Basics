//-------------------------------------------------------------------------------------
void TelnetHandler::processPythonCommand(std::string command)
{
	if(pTelnetServer_->pScript() == NULL || command.size() == 0)
		return;
	
	command += "\n";
	PyObject* pycmd = PyUnicode_DecodeUTF8(command.data(), command.size(), NULL);
	if(pycmd == NULL)
	{
		SCRIPT_ERROR_CHECK();
		return;
	}

	DEBUG_MSG(boost::format("TelnetHandler::processPythonCommand: size(%1%), command=%2%.\n") % 
		command.size() % command);

	std::string retbuf = "";
	PyObject* pycmd1 = PyUnicode_AsEncodedString(pycmd, "utf-8", NULL);

	pTelnetServer_->pScript()->run_simpleString(PyBytes_AsString(pycmd1), &retbuf);

	if(retbuf.size() > 0)
	{
		// 将结果返回给客户端
		Mercury::Bundle bundle;
		bundle << retbuf;
		bundle.send(*pEndPoint_);
		sendEnter();
	}

	Py_DECREF(pycmd);
	Py_DECREF(pycmd1);
}