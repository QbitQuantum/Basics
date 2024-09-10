// return 0 if message type is not 1,2,3,4
int fetchReceivedMessage(struct MESSAGE* p, char* buf)
{
	p->msgType = (int)buf[0];
	int* path=NULL;
	int i;
	switch(p->msgType){
	case 1:
		p->dest = byte2int(&buf[1]);
    		strcpy(p->message, &buf[3]);
    		printf("%d fetchReceivedMessage: ",pGlobalTopo->myaddr);
    		printMESSAGE(buf);
    	return 1;
	case 2:
		path = (int*)(buf+1);
		p->hopNum = path[0];
		memcpy(p->path,&path[1],sizeof(int)*p->hopNum);
		strcpy(p->message,buf+1+sizeof(int)*(p->hopNum+1));
		p->src = p->path[0];
		p->dest = p->path[p->hopNum-1];
		printf("%d fetchReceivedMessage: ",pGlobalTopo->myaddr);
    		printMESSAGE(buf);
		return 2;
	case 3:
		memcpy(&p->linkinfo,&buf[1],sizeof(struct LINK));
		return 3;
	case 4:
		memcpy(&p->linkinfo,&buf[1],sizeof(struct LINK));
		return 4;
	default: 
		printf("Unknown UDP fetchReceivedMessage\n");
		return 0;
	}
}