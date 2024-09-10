bool GraphDog::command(const std::vector<CommandParam>& params)
{
	string udid=getUdid();
    string email=getEmail();
    string auid=getAuID();
    string token;
	//저장되어있는 토큰불러오기. 없으면 생성
    token=getToken();
	
	int insertIndex = AutoIncrease::get();
	std::vector<CommandType> cmdCollect;
	CommandsType cmdQueue;
	// cmdQueue 에 명령 추가하고...
	JsonBox::Object jsonTotalCmd;
	cmdQueue.chunk = GDStruct((char*)malloc(1), 0, CURLE_AGAIN);
	int i=0;
	for(std::vector<CommandParam>::const_iterator iter = params.begin(); iter != params.end(); ++iter, i++)
	{
		ostringstream oss;
		oss << (iter->param);
		
		char buf[20];
		sprintf(buf, "%d", i);
		JsonBox::Object param;
		param["p"] = iter->param;
		param["a"] = iter->action;
		jsonTotalCmd[buf] = param; // dict 로
		CommandType cmd = {iter->target, iter->selector, oss.str(), iter->action};
		cmdQueue.commands[buf] = cmd;
		cmdCollect.push_back(cmd);
	}
	ostringstream oss2;
	oss2 << jsonTotalCmd;
	cmdQueue.commandStr = oss2.str();
	cmdQueue.caller = this;
	commandQueue[insertIndex] = cmdQueue;
	pthread_t p_thread;
	int thr_id;
	
	// 쓰레드 생성 아규먼트로 1 을 넘긴다.
	thr_id = pthread_create(&p_thread, NULL, t_function, (void*)insertIndex);
	if (thr_id < 0)
	{
		//쓰레드생성오류시
		JsonBox::Object resultobj;
		resultobj["state"]= JsonBox::Value("error");
		resultobj["errorMsg"]=JsonBox::Value("don't create thread");
		resultobj["errorCode"]=JsonBox::Value(1001);
		
		for(std::vector<CommandType>::const_iterator iter = cmdCollect.begin(); iter != cmdCollect.end(); ++iter)
		{
			if( iter->target != 0 && iter->selector != 0)
				((iter->target)->*(iter->selector))(resultobj);	
		}
		
		if( cmdQueue.chunk.memory )
			free(cmdQueue.chunk.memory);
		commandQueue.erase(insertIndex);
		return false;
	}
	
    return true;
}