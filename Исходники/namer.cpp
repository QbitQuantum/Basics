int main(void)
{
	Connection *cnxn = Connection::CreateService("namer");
	Message msg, reply;

	do_namer_register(NAMER_PORT,"namer");

	while(cnxn->Recv(&msg) == 0){
		int32 op = -1;
		int32 port = -1;
		const char *name = 0;
		int32 res = -1;
	
		msg.GetInt32('code',&op);
		msg.GetInt32('port',&port);
		msg.GetString('name',&name);
		
		switch(op){
		case NAMER_FIND:
			res = do_namer_find(name);
			break;
			
		case NAMER_REGISTER:
			res = do_namer_register(port, name);
			break;
		}
		
		reply.Empty();
		reply.PutInt32('resp',res);
		msg.Reply(&reply);
	}
	
	return 0;
}