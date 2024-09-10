RandomWalk::~RandomWalk(){
	TerminateThread(hCollectData, 0);
	TerminateThread(hProccessData, 0);
}