void OscKinectServer::init(){
	gui.setup("kinect at " + getHostName() + ":" + ofToString(getPort()));
	gui.add(tilt.setup("tilt",0,-30,30,300));
	gui.add(nearThreshold.setup("nearThreshold",0,0,255,300));
	gui.add(farThreshold.setup("farThreshold",0,0,255,300));
	gui.add(nearClip.setup("nearClip",3000,0,10000,300));
	gui.add(farClip.setup("farClip",6500,0,10000,300));
	gui.add(record.setup("record",false));
	gui.add(player.setup("use player",false));

	tilt.addListener(this,&OscKinectServer::tiltChanged);
	nearThreshold.addListener(this,&OscKinectServer::nearThresholdChanged);
	farThreshold.addListener(this,&OscKinectServer::farThresholdChanged);
	nearClip.addListener(this,&OscKinectServer::clipChanged);
	farClip.addListener(this,&OscKinectServer::clipChanged);
	record.addListener(this,&OscKinectServer::recordPressed);
	player.addListener(this,&OscKinectServer::usePlayer);
}