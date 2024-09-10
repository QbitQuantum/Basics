bool Mgr::start(){
	while(true){
		if(!ProcessCmd())
			break;
		obj->update();
		_sleep(10);
	}
	return true;
}