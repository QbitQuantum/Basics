void AriaClientDriver::controlloop(){
	ros::Rate myLoopRate(10);
	sendInput();
	ros::spinOnce();
	myLoopRate.sleep();
}