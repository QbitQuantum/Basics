//http://www.tuicool.com/articles/YNZ7Jj
void* ResPonseThread::threadFunc(void *arg)
{
	ResPonseThread* thred=(ResPonseThread*)arg;	
	ODSocket csocket = SocketThread::GetInstance()->getSocket();
	if(SocketThread::GetInstance()->state==0)
	{
		while (true)
		{
			//have message come
			if (csocket.Select() == -2)
			{
				//deduct 2 head_length, 
				unsigned char recvLen[2]; //must less 65535 bytes
				memset(recvLen, 0, sizeof(recvLen));
				int actualRecvLen = csocket.Recv((char*)recvLen, sizeof(recvLen), 0);
				//log("actualRecvLen = %d", actualRecvLen);
				if (HEAD_LEN == actualRecvLen)
				{
					//the rest data
					int tLen = ((int)recvLen[0] << 8) + recvLen[1];
					char* recvBuf = new char[tLen];
					memset(recvBuf, 0, tLen);
					int recvResult = csocket.Recv(recvBuf, tLen, 0);
					std::string resultJson(recvBuf, tLen);
					log(" recveBuf =======>  %s ", recvBuf);
					delete[] recvBuf;
					recvBuf = nullptr;

					//json parse
					do
					{
						rapidjson::Document *_doc = new rapidjson::Document;
						_doc->Parse<0>(resultJson.c_str());
						CC_BREAK_IF(_doc->HasParseError());
						if (!_doc->IsObject())
							break;
						if (_doc->HasMember("Type"))
						{
							//to do 
							const rapidjson::Value &pType = _doc->operator[]("Type");
							std::string type = pType.GetString();
							Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
								Director::getInstance()->getEventDispatcher()->setEnabled(true);
								if (type == "LoginResult")
								{
									Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(FIND_DEVICE_MSG, (void *)_doc);
								}
								else if (type == "Joystick")
								{
									Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CONTROLLER_JOYSTICK_MSG, (void *)_doc);
								}
								else if (type == "Shock")
								{
									Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CONTROLLER_SHOCK_MSG, (void *)_doc);
								}
								else if (type == "SwapPositionResult")
								{
									Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(CUSTOM_SWAP_POSITION_MSG, (void *)_doc);
								}
								else if (type == "ResponseJoystickStatus")
								{
									Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(REPORT_JOYSTICK_STATUS_MSG, (void *)_doc);
								}
								delete _doc;
							});
						}
						else
						{
							delete _doc;
						}
					} while (0);
				}
				else
				{
					//log("ResPonseThread::threadFunc(void *arg) : exit !!! 2");
					////disconnect
					//break;
				}


			}//if (csocket.Select() == -2)

			//close socket -> exit thread !
			if (thred->isExit())
			{
				log("ResPonseThread::threadFunc(void *arg) : thred->isExit()");
				break;
			}
					
		}//while (true)
	}//if(SocketThread::GetInstance()->state==0)
	return NULL;
}