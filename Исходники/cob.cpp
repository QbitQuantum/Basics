void jointCallback(const sensor_msgs::JointState & msg){
	ROS_INFO("RECEIVED JOINT VALUES");
	if(itHappened){
		sub.shutdown();
		cout<<"not again"<<endl;
		return;
	}
	if (msg.name.size()== 6 ) {
	itHappened=true;
	for (int i=0;i<6;i++){
	joint_pos[i] = msg.position[i];
	name[i] = msg.name[i];
//	cout<<" , "<<name[i]<<":"<<joint_pos[i];
	}
	sub.shutdown();
	}
}