void VariableView::updateVision(NaoData *naoData) {
   Blackboard *blackboard = (naoData->getCurrentFrame().blackboard);
   if (!blackboard) return;

   std::vector<FootInfo>         feet          = readFrom (vision, feet);
   std::vector<BallInfo>         balls         = readFrom (vision, balls);
   BallHint                      ballHint      = readFrom (vision, ballHint);
   std::vector<PostInfo>         posts         = readFrom (vision, posts);
   std::vector<RobotInfo>        robots        = readFrom (vision, robots);
   std::vector<FieldEdgeInfo>    fieldEdges    = readFrom (vision, fieldEdges);
   std::vector<FieldFeatureInfo> fieldFeatures = readFrom (vision, fieldFeatures);
   Odometry                      dualOdometry  = readFrom (vision, dualOdometry);
   Odometry                      motionOdometry  = readFrom (motion, odometry);
   bool                          caughtLeft    = readFrom (vision, caughtLeft);
   bool                          caughtRight   = readFrom (vision, caughtRight);
   std::pair<int, int>           dxdy          = readFrom (vision, dxdy);

   float headYaw  = readFrom(motion, sensors).joints.angles[Joints::HeadYaw];
   float headYawK  = readFrom(kinematics, sensorsLagged).joints.angles[Joints::HeadYaw];
   uint32_t total = readFrom(perception, total);

   times.push_back(total);
   if (times.size() > 10) times.pop_front();
   int sum = 0;
   for (unsigned int i = 0; i < times.size(); i++) sum += times[i];
   float fps = 1000000.0/total;


   perceptionAverageFPS->setText(0, createSufPref("Framerate: ", fps, " fps"));
   perceptionKinematicsTime->setText(0, createSufPref("Kinematics time: ", readFrom(perception, kinematics), ""));
   perceptionVisionTime->setText(0, createSufPref("Vision time: ", readFrom(perception, vision), ""));
   perceptionLocalisationTime->setText(0, createSufPref("Localisation time: ", readFrom(perception, localisation), ""));
   perceptionBehaviourTime->setText(0, createSufPref("Behaviour time: ", readFrom(perception, behaviour), ""));
   perceptionTotalTime->setText(0, createSufPref("Total time: ", total, ""));

   visionTimestamp->setText(0, createSufPref("Timestamp: ", readFrom(vision, timestamp), ""));
   if(caughtLeft){
      visionTurn->setText(0, createSufPref("Caught on LHS!\nDual Odom Turn: ", RAD2DEG(dualOdometry.turn), " deg"));
   } else if (caughtRight){
      visionTurn->setText(0, createSufPref("Caught on RHS!\nDual Odom Turn: ", RAD2DEG(dualOdometry.turn), " deg"));
   } else {
      visionTurn->setText(0, createSufPref("Not Caught.\nDual Odom Turn: ", RAD2DEG(dualOdometry.turn), " deg"));
   }
   visionFrames->setText(0, createSufPref("Odom missed frames: ", readFrom(vision, missedFrames), ""));
   visionGoalProb->setText(0, createSufPref("Away Goal Prob: ", readFrom(vision, awayGoalProb), ""));
   visionHomeMapSize->setText(0, createSufPref("Home Map Size: ", readFrom(vision, homeMapSize), ""));
   visionAwayMapSize->setText(0, createSufPref("Away Map Size: ", readFrom(vision, awayMapSize), ""));
   visionGoal->setText(0, createSufPref("Goal Area: ", PostInfo::TypeName[readFrom(vision, goalArea)], ""));

   stringstream sdxdy;
   sdxdy << "Vision DxDy: (" << dxdy.first << "," << dxdy.second << ")";
   visionDxdy->setText(0, sdxdy.str().c_str());


   stringstream sBallPos;

   sBallPos << "BallHint: " << BallHint::TypeName[ballHint.type] << "\n";

   int numBalls = balls.size ();
   if (numBalls == 0) {
   } else {
      Point ballLocation = balls[0].imageCoords;
      sBallPos << "Ball is at (" << ballLocation.x() <<
         ", " << ballLocation.y () << ")";
   }
   visionBallPos->setText(0, sBallPos.str().c_str());

   stringstream s;

   int numEdges = fieldEdges.size ();
   RANSACLine edges[MAX_FIELD_EDGES];

   for (int i = 0; i < numEdges; ++ i) {
      edges[i] = fieldEdges[i].rrEdge;
   }


   s << "numEdges " << numEdges << endl;
   for (int i = 0; i < numEdges; i++) {
      s << "Edge 1: " << edges[i].t1 << "x + " << edges[i].t2 <<
         "y + " << edges[i].t3 << endl;
   }

   s.str ("");
   s << "Post Type 1 = " << PostInfo::TypeName[PostInfo::pNone]; 
   visionPostType1->setText (0, s.str ().c_str ());

   s.str ("");
   s << "Post Type 2 = " << PostInfo::TypeName[PostInfo::pNone]; 
   visionPostType2->setText (0, s.str ().c_str ());

   visionPost1->setText (0, "Post 1 @ ");
   visionPost2->setText (0, "Post 2 @ ");
   visionPostInfo1->setText (0, "P1 - ");
   visionPostInfo2->setText (0, "P2 - ");


   if (posts.size () > 0) {
      PostInfo p = posts[0];
      RRCoord rr = posts[0].rr;

      s.str ("");
      s << "Post Type 1 = " << PostInfo::TypeName[posts[0].type]; 
      visionPostType1->setText (0, s.str ().c_str ());

      s.str ("");
      s << "Post 1 @ " 
        << rr.distance() << ", " << RAD2DEG(rr.heading()) << ", " << rr.heading()
        << ", (" << rr.var(0,0) << ", " << rr.var(1,1) << ")";
      visionPost1->setText (0, s.str ().c_str ());

      s.str ("");
      s << "P1 - Trust = " << p.trustDistance;
      s << ", dir = " << PostInfo::DirName[p.dir];
      visionPostInfo1->setText (0, s.str ().c_str ());
   }

   if (posts.size () > 1) {
      PostInfo p = posts[1];
      RRCoord rr = posts[1].rr;

      s.str ("");
      s << "Post Type 2 = " << PostInfo::TypeName[posts[1].type]; 
      visionPostType2->setText (0, s.str ().c_str ());

      s.str ("");
      s << "Post 2 @ " 
        << rr.distance() << ", " << RAD2DEG(rr.heading()) << ", " << rr.heading()
        << ", (" << rr.var(1,1) << ", " << rr.var(2,2) << ")";
      visionPost2->setText (0, s.str ().c_str ());

      s.str ("");
      s << "P2 - Trust = " << p.trustDistance;
      s << ", dir = " << PostInfo::DirName[p.dir];
      visionPostInfo2->setText (0, s.str ().c_str ());

   }

   stringstream sBallPosRelative;
   if(numBalls > 0) {
      sBallPosRelative << "Ball @ " << balls[0].rr.distance() << ", " <<
         RAD2DEG(balls[0].rr.heading()) << ", " << balls[0].rr.heading();
   }
   visionBallPosRobotRelative->setText(0, sBallPosRelative.str().c_str());

   this->visionNumBalls->setText(0,createSufPref("# Balls: ", numBalls, ""));

   int numFeet = feet.size();
   this->visionNumFeet->setText(0,createSufPref("# Feet: ", numFeet, ""));

   stringstream foot1;
   foot1 << "Foot 1: ";
   stringstream foot2;
   foot2 << "Foot 2: ";
   if (numFeet > 0) {
      foot1 << "(" << feet[0].imageCoords[0] << "," << feet[0].imageCoords[1] << ")" << endl;
      foot1 << "  d:" << feet[0].rr.distance() << " h:" << feet[0].rr.heading();
      if (numFeet > 1) {
         foot2 << "(" << feet[1].imageCoords[0] << "," << feet[1].imageCoords[1] << ")" << endl;
         foot2 << "  d:" << feet[1].rr.distance() << " h:" << feet[1].rr.heading();
      }
   }
   visionFoot1->setText(0, foot1.str().c_str());
   visionFoot2->setText(0, foot2.str().c_str());

   stringstream odom;
   odom.str("");
   odom << "Fwd = " << motionOdometry.forward;
   motionForwardOdom->setText (0, odom.str ().c_str ());

   odom.str("");
   odom << "Left = " << motionOdometry.left;
   motionLeftOdom->setText (0, odom.str ().c_str ());

   odom.str("");
   odom << "Turn = " << motionOdometry.turn;
   motionTurnOdom->setText (0, odom.str ().c_str ());

   stringstream head;
   head.str("");
   head << "HeadYaw = " << headYaw;
   motionHeadYaw->setText (0, head.str ().c_str ());

   head.str("");
   head << "HeadYawK = " << headYawK;
   kinematicsHeadYaw->setText (0, head.str ().c_str ());

}