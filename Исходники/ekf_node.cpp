 // Gets camera velocities. Also, if target not visible (i.e. estimatorOn = false) publishes output (ground truth)
 // and does prediction 
 void camVelCB(const geometry_msgs::TwistStampedConstPtr& twist)
 {
     // Time
     ros::Time timeStamp = twist->header.stamp;
     double timeNow = timeStamp.toSec();
     double delT = timeNow - lastVelTime;
     lastVelTime = timeNow;
     
     // Camera velocities, expressed in camera coordinate system
     vCc << twist->twist.linear.x,twist->twist.linear.y,twist->twist.linear.z;
     wGCc << twist->twist.angular.x,twist->twist.angular.y,twist->twist.angular.z;
     
     if (!estimatorOn)
     {
         // Object trans w.r.t. image frame, for ground truth
         Vector3d trans;
         tf::StampedTransform transform;
         tfl.waitForTransform("image","ugv0",timeStamp,ros::Duration(0.1));
         tfl.lookupTransform("image","ugv0",timeStamp,transform);
         tf::Vector3 temp_trans = transform.getOrigin();
         trans << temp_trans.getX(),temp_trans.getY(),temp_trans.getZ();
         
         // Ground truth
         Vector3d x;
         x << trans.segment<2>(0)/trans(2),1/trans(2);
         xlast << x; // Update for optical flow
         
         // Object rotation w.r.t. image frame, for rotating target velocities into image coordinates
         try
         {
             Quaterniond quat;
             if (deadReckoning)
             {
                 tf::StampedTransform tfImage2World;
                 tf::StampedTransform tfOdom2Marker;
                 tfl.waitForTransform("image","world",timeStamp,ros::Duration(0.1));
                 tfl.lookupTransform("image","world",timeStamp,tfImage2World);
                 tfl.waitForTransform("ugv0/odom","ugv0/base_footprint",timeStamp,ros::Duration(0.1));
                 tfl.lookupTransform("ugv0/odom","ugv0/base_footprint",timeStamp,tfOdom2Marker);
                 
                 tf::Quaternion temp_quat = tfImage2World.getRotation();
                 Quaterniond qIm2W = Quaterniond(temp_quat.getW(),temp_quat.getX(),temp_quat.getY(),temp_quat.getZ());
                 temp_quat = tfOdom2Marker.getRotation();
                 Quaterniond qO2M = Quaterniond(temp_quat.getW(),temp_quat.getX(),temp_quat.getY(),temp_quat.getZ());
                 quat = qIm2W*qWorld2Odom*qO2M;
             }
             else
             {
                 tf::Quaternion temp_quat = transform.getRotation();
                 quat = Quaterniond(temp_quat.getW(),temp_quat.getX(),temp_quat.getY(),temp_quat.getZ());
             }
             
             // Target velocities expressed in camera coordinates
             Vector3d vTc = quat*vTt;
             
             // Update so that delT in featureCB is reasonable after switch
             lastImageTime = timeNow;
             
             // Convert to scalars to match notation in papers
             double vc1 = vCc(0);        double vc2 = vCc(1);        double vc3 = vCc(2);
             double vq1 = vTc(0);        double vq2 = vTc(1);        double vq3 = vTc(2);
             double w1 = wGCc(0);        double w2 = wGCc(1);        double w3 = wGCc(2);
             double x1hat = xhat(0);     double x2hat = xhat(1);     double x3hat = xhat(2);
             
             // Predictor
             double Omega1 = w3*x2hat - w2 - w2*pow(x1hat,2) + w1*x1hat*x2hat;
             double Omega2 = w1 - w3*x1hat - w2*x1hat*x2hat + w1*pow(x2hat,2);
             double xi1 = (vc3*x1hat - vc1)*x3hat;
             double xi2 = (vc3*x2hat - vc2)*x3hat;
             
             double x1hatDot = Omega1 + xi1 + vq1*x3hat - x1hat*vq3*x3hat;
             double x2hatDot = Omega2 + xi2 + vq2*x3hat - x2hat*vq3*x3hat;
             double x3hatDot = vc3*pow(x3hat,2) - (w2*x1hat - w1*x2hat)*x3hat - vq3*pow(x3hat,2);
             
             // Predict Covariance
             Matrix3d F = calculate_F(xhat,vCc,vTc,wGCc);
             MatrixXd Pdot = F*P+P*F.transpose() + Q;
             
             // Update states and covariance
             Vector3d xhatDot;
             xhatDot << x1hatDot, x2hatDot, x3hatDot;
             xhat += xhatDot*delT;
             P += Pdot*delT;
             
             // Publish output
             publishOutput(x,xhat,trans,timeStamp);
         }
         catch (tf::TransformException e)
         {
         }
     }
 }