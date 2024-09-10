int main(int argc, char **argv)
{
    ros::init(argc, argv, "Quadcopter Extended Kalman Filter: version 1, ORB SLAM only"); //Ros Initialize
    ros::start();
    ros::Rate loop_rate(T); //Set Ros frequency to 50/s (fast)

    ros::Time measuredOn(1.0);
    ros::Time measuredOff(2.0);

    // FIXME: Make variable names clearer or add comments next to them
    ros::NodeHandle nh_, ph_, gnh_, ph("~");
    ros::Subscriber pos_sub_ ;
    ros::Subscriber ipt_sub_,ap_sub_ ,measured_sub_;
    ros::Subscriber imu_sub_ ;
    ros::Publisher gl_pub_ , vel_pub_, gl2_pub_;

    spawn.pose.position.x = transformX;
    spawn.pose.position.y = transformY;
    


    void poseCallback(const tf2_msgs::TFMessage::ConstPtr& pose);
    void iptCallback(const tf2_msgs::TFMessage::ConstPtr&);
    void imuCallback(const ardrone_autonomy::Navdata::ConstPtr&);
    void clearAll();
    // ROS stuff
    // Other member variables
    
    stationary = false;
    double ux=0;
    double uy=0;
    double vx=0;
    double vy=0;
    double uz=0;
    double maxVelFactor=1.25;
    
    Q(0,0)=0;
    Q(1,1)=0;
    Q(2,2)=0;
    Q(3,3)=0;
    R(0,0)=.01;
    R(1,1)=.01;
    R(2,2)=.01;
    R(3,3)=.01;
    P(0,0)=1000;
    P(1,1)=1000;
    P(2,2)=1000;
    P(3,3)=1000;
    V(0)=0;
    V(1)=0;
    V(2)=0;
    Z(0)=0;
    Z(1)=0;
    Z(2)=0;
    Z(3)=0;
    VZ(0)=0;
    VZ(1)=0;
    VZ(2)=0;
    
    
    poseEstimation[0].header.frame_id="Gypsy Danger";
    //poseEstimation[1].header.frame_id="Typhoon";
    poseEstimation[5].header.frame_id="leonardo";
    poseEstimation[2].header.frame_id="michelangelo";
   poseEstimation[3].header.frame_id="donatello";
    poseEstimation[9].header.frame_id="ghiberti";
     poseEstimation[6].header.frame_id="boticelli";
poseEstimation[8].header.frame_id="bellini";
poseEstimation[7].header.frame_id="giotto";
poseEstimation[4].header.frame_id="raphael";
poseEstimation[1].header.frame_id="titian";
poseEstimation[10].header.frame_id="masaccio";

poseEstimation[41].header.frame_id="picasso";
poseEstimation[42].header.frame_id="dali";
poseEstimation[43].header.frame_id="goya";
    poseEstimationTF.transforms.resize(num);
    twistEstimation.transforms.resize(num);
    for (int i=0;i<num;i++){
		numb[i]=0;
            poseEstimation[i].pose.position.x=0;
            poseEstimation[i].pose.position.y=0;
            poseEstimation[i].pose.position.z=0;
            poseEstimation[i].pose.orientation=tf::createQuaternionMsgFromYaw(0);
            T1[i]=ros::Time::now().toSec();
            T2[i]=ros::Time::now().toSec();
            got_pose_[i] = false;
            Vmatrix[i].resize(5,3);
            X[i].resize(4,1);
            active[i]=false;
	    poseEstimationTF.transforms[i].transform.rotation.w=1;
            twistEstimation.transforms[i].transform.rotation.w=1;
	    poseEstimationTF.transforms[i].header.frame_id="null";
    }

	geometry_msgs::PoseStamped zeroStamped;
	
    

    pos_sub_= nh_.subscribe<tf2_msgs::TFMessage>("/tf", 25,poseCallback);
    imu_sub_= nh_.subscribe<ardrone_autonomy::Navdata>("/ardrone/navdata", 1,imuCallback);
    ipt_sub_=nh_.subscribe<tf2_msgs::TFMessage>("/cmd_vel",25,iptCallback);
    ap_sub_=nh_.subscribe<turtlebot_deployment::PoseWithName>("/all_positions",25 ,apCallback);
    measured_sub_=nh_.subscribe<std_msgs::Header>("/measurementFlag",25 ,mFlag);
    gl_pub_ = gnh_.advertise<geometry_msgs::PoseStamped>("/poseEstimation", 1000, true);
    gauss_Boundary = gnh_.advertise<std_msgs::Bool>("/gauss/boundaryFlag", 1000, true);
    gl2_pub_ = gnh_.advertise<tf2_msgs::TFMessage>("/poseEstimationC", 1000, true);
    vel_pub_ = gnh_.advertise<tf2_msgs::TFMessage>("/velocityEstimation", 1000, true);
    linearObstacle=gnh_.advertise<geometry_msgs::PoseStamped>("linearObstacle",1000,true);
    voronoiDeploymentCTerm = gnh_.advertise<std_msgs::Float32>("/voronoi/deploymentOptions/CTERM", 1000, true);
    voronoiDeploymentKTerm = gnh_.advertise<std_msgs::Float32>("/voronoi/deploymentOptions/KTERM", 1000, true);

ekf_Switch[MICHELANGELO_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/michelangelo/toKalmanfilter", 1000, true);
ekf_Switch[DONATELLO_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/donatello/toKalmanfilter", 1000, true);
ekf_Switch[RAPHAEL_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/raphael/toKalmanfilter", 1000, true);
ekf_Switch[LEONARDO_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/leonardo/toKalmanfilter", 1000, true);
ekf_Switch[BOTICELLI_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/boticelli/toKalmanfilter", 1000, true);
ekf_Switch[GIOTTO_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/giotto/toKalmanfilter", 1000, true);
ekf_Switch[BELLINI_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/bellini/toKalmanfilter", 1000, true);
ekf_Switch[GHIBERTI_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/ghiberti/toKalmanfilter", 1000, true);
ekf_Switch[MASACCIO_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/masaccio/toKalmanfilter", 1000, true);
ekf_Switch[TITIAN_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/titian/toKalmanfilter", 1000, true);
ekf_Switch[PICASSO_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/picasso/toKalmanfilter", 1000, true);
ekf_Switch[DALI_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/dali/toKalmanfilter", 1000, true);
ekf_Switch[GOYA_INDEX]    = gnh_.advertise<turtlebot_deployment::PoseWithName>("/goya/toKalmanfilter", 1000, true);

    while (ros::ok()) 
    {
        for (int i=0;i<num;i++){
        got_pose_[i] = false;
        got_vel_[i]  = false;
        }        
        ros::spinOnce();
        for (int i=0;i<num;i++){
            if (active[i]==true){
                MatrixXf& b = Vmatrix[i];
                MatrixXf& Xx = X[i];
            
			    //Conditionals
			if (got_pose_[i] == true)
			{
			    cout<<"got_pose_: "<<got_pose_[i]<<"\n";
			    R(0,0)=1;
			    R(1,1)=1;
			    R(2,2)=1;
			    R(3,3)=1;
			    
			    
			b(4,0)=b(3,0);
			b(3,0)=b(2,0);
			b(2,0)=b(1,0);
			b(1,0)=b(0,0);
			b(0,0)=(measurementPose[i].pose.position.x-xOld[i])/(T2[i]-T1[i]);
		
			b(4,1)=b(3,1);
			b(3,1)=b(2,1);
			b(2,1)=b(1,1);
			b(1,1)=b(0,1);
			b(0,1)=(measurementPose[i].pose.position.y-yOld[i])/(T2[i]-T1[i]);
		
			b(4,2)=b(3,2);
			b(3,2)=b(2,2);
			b(2,2)=b(1,2);
			b(1,2)=b(0,2);
			b(0,2)=(measurementPose[i].pose.position.z-zOld[i])/(T2[i]-T1[i]);
		
	
			
		
			}
			else
			{
			    R(0,0)=10000;
			    R(1,1)=10000;
			    R(2,2)=10000;
			    R(3,3)=10000;
			}
		
			if (stationary==true )
			{
			    Q(0,0)=0;
			    Q(1,1)=0;
			    Q(2,2)=0;
			    Q(3,3)=0;
			}
			else
			{
			    Q(0,0)=100;
			    Q(1,1)=100;
			    Q(2,2)=100;
			    Q(3,3)=100;
			}

			Matrix4f temp;
			    
			//Stage 1
			ux=twist[i].linear.x*cos(yaw[i])-twist[i].linear.y*sin(yaw[i]);
			uy=-twist[i].linear.y*cos(yaw[i])+twist[i].linear.x*sin(yaw[i]);
			uz=twist[i].linear.z;
		
			vXTot=(b(2,0)+b(1,0)+b(0,0))/3;
			vYTot=(b(2,1)+b(1,1)+b(0,1))/3;
			vZTot=(b(2,2)+b(1,2)+b(0,2))/3;
			//std::cout<<"\n Measured Velocity: \n"<<vXTot<<"\n";
			// if (ux>1){
			//     ux=1;
			// }
			// else if (ux<-1){
			//     ux=-1;
			// }
			// if (uy>1){
			//     uy=1;
			// }
			// else if (uy<-1){
			//     uy=-1;
			// }
			// if (ux*maxVelFactor<vx && ux>0){
			//     ux=0;
			// }
			// else if(ux*maxVelFactor>vx && ux<0){
			//     ux=0;
			// }
		
			// if (uy*maxVelFactor<vy && uy>0){
			//     uy=0;
			// }
			// else if(uy*maxVelFactor>vy && uy<0){
			//     uy=0;
			// }    
		
		
			// V << V(0)+ .6*ux/T,V(1)+.6*uy/T,V(2)+.6*uz/T;
			// VZ << measurementTwist.linear.x,measurementTwist.linear.y,measurementTwist.linear.y;
			 Z << measurementPose[i].pose.position.x,measurementPose[i].pose.position.y,measurementPose[i].pose.position.z,yaw[i];
			// X << X(0)+ V(0)/T,X(1)+V(1)/T,X(2)+V(2)/T,X(3)+twist.angular.z/T;
			
				Xx << Xx(0)+ ux/T,Xx(1)+uy/T,Xx(2)+uz/T,Xx(3)+twist[i].angular.z/T;
			



			//Stage 2
			if (got_pose_[i] == true)
			{
			    A << 1, 0,0, -twist[i].linear.x/T*sin(yaw[i])-twist[i].linear.y/T*cos(yaw[i]),0, 1,0, twist[i].linear.x/T*cos(yaw[i])+twist[i].linear.y/T*sin(yaw[i]),0, 0, 1,0, 0,0,0,-1;
			    P = A*P*A.transpose() + W*Q*W.transpose();

			    //Stage 3
			    temp = (W*P*W.transpose() + W*R*W.transpose());
			    K = P*W.transpose()*temp.inverse();

			    //Stage 4
			    Xx = Xx + K*(Z-Xx);

			    //Stage 5
			    P = (I - K*W)*P;
			    V(0)=vXTot;
			    V(1)=vYTot;
			    V(2)=vZTot;
			}

			if (i>10){
				V(0)=ux;
				V(1)=uy;
			}


			    twistEstimation.transforms[i].transform.translation.x=V(0);
			    twistEstimation.transforms[i].transform.translation.y=V(1);
			    twistEstimation.transforms[i].transform.translation.z=V(2);

			if (poseEstimation[i].pose.position.x==Xx(0) && poseEstimation[i].pose.position.y==Xx(1)){
				numb[i]=numb[i]+1;
			}
			else{
				numb[i]=0;
			}
			poseEstimation[i].pose.position.x = Xx(0);
			poseEstimation[i].pose.position.y = Xx(1);
			poseEstimation[i].pose.position.z = Xx(2);
			poseEstimation[i].pose.orientation = tf::createQuaternionMsgFromYaw(Xx(3));

			if (poseEstimation[i].header.frame_id.compare("obstacle")==0 || (i >0 && i<11) || (i>40&&i<44)){
			poseEstimation[i].pose.position.x = Z(0);
			poseEstimation[i].pose.position.y = Z(1);
			poseEstimation[i].pose.position.z = Z(2);
			poseEstimation[i].pose.orientation = tf::createQuaternionMsgFromYaw(Z(3));
			}
			if (Z(0)==0 &&Z(1)==0){
			poseEstimation[i].pose.position.x = 0;
			poseEstimation[i].pose.position.y = 0;
			}

			
			gl_pub_.publish(poseEstimation[i]);

			

			poseEstimationTF.transforms[i].transform.translation.x=poseEstimation[i].pose.position.x;
			poseEstimationTF.transforms[i].transform.translation.y=poseEstimation[i].pose.position.y;
			poseEstimationTF.transforms[i].transform.translation.z=poseEstimation[i].pose.position.z;

			poseEstimationTF.transforms[i].transform.rotation.x=poseEstimation[i].pose.orientation.x;
			poseEstimationTF.transforms[i].transform.rotation.y=poseEstimation[i].pose.orientation.y;
			poseEstimationTF.transforms[i].transform.rotation.z=poseEstimation[i].pose.orientation.z;
			poseEstimationTF.transforms[i].transform.rotation.w=poseEstimation[i].pose.orientation.w;

			poseEstimationTF.transforms[i].header.frame_id=poseEstimation[i].header.frame_id;

			if (numb[i]>100){
				poseEstimation[i].pose.position.x=0;
				poseEstimation[i].pose.position.y=0;
				poseEstimation[i].pose.position.z=0;
				active[i]=false;

			poseEstimationTF.transforms[i].transform.translation.x=0;
			poseEstimationTF.transforms[i].transform.translation.y=0;
			poseEstimationTF.transforms[i].transform.translation.z=0;
				
			}


			//std::cout<<"\n Measured: \n"<<measurementPose[i]<<"\n";
			//std::cout<<"Twist: \n"<<twist<<"\n";
			//std::cout<<"Best Estimation\n"<<poseEstimation[i]<<"\n---------\n\n";
			//std::cout<<"Yaw: "<<yaw[i]<<"\n---------\n\n";
			//std::cout<<"--------------------------------------------------------------------";
		       
			    }else{

			}
			
			
			    
			}
		     vel_pub_.publish(twistEstimation);
	             gl2_pub_.publish(poseEstimationTF);
		     loop_rate.sleep();
        }
        
}