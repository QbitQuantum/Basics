ActorStateMachine::~ActorStateMachine(void)
{
	FnScene scene;
	scene.Object(sID);
	scene.DeleteObject(this->bloodID);
	/*
	FnWorld gw;
	gw.Object(gID);
	gw.DeleteAudio(audioG);
	gw.DeleteAudio(audioD);
	*/
}