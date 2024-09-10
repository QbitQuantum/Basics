 void CANPriusNode::spin() {
   _canConnection = std::make_shared<CANConnection>(_canDeviceStr);
   PRIUSReader reader(*_canConnection);
   Timer timer;
   while (_nodeHandle.ok()) {
     try {
       std::shared_ptr<PRIUSMessage> message = reader.readMessage();
       const ros::Time timestamp = ros::Time::now();
       if (message->instanceOf<FrontWheelsSpeed>()) {
         const FrontWheelsSpeed& fws = message->typeCast<FrontWheelsSpeed>();
         publishFrontWheelsSpeed(timestamp, fws);
       }
       else if (message->instanceOf<RearWheelsSpeed>()) {
         const RearWheelsSpeed& rws = message->typeCast<RearWheelsSpeed>();
         publishRearWheelsSpeed(timestamp, rws);
       }
       else if (message->instanceOf<Speed1>()) {
         const Speed1& sp = message->typeCast<Speed1>();
       }
       else if (message->instanceOf<Speed2>()) {
         const Speed2& sp = message->typeCast<Speed2>();
       }
       else if (message->instanceOf<Speed3>()) {
         const Speed3& sp = message->typeCast<Speed3>();
       }
       else if (message->instanceOf<Steering1>()) {
         const Steering1& st = message->typeCast<Steering1>();
         publishSteering1(timestamp, st);
       }
       else if (message->instanceOf<Steering2>()) {
         const Steering2& st = message->typeCast<Steering2>();
       }
       else if (message->instanceOf<Brakes>()) {
         const Brakes& b = message->typeCast<Brakes>();
       }
       else if (message->instanceOf<Acceleration1>()) {
         const Acceleration1& a = message->typeCast<Acceleration1>();
       }
       else if (message->instanceOf<Acceleration2>()) {
         const Acceleration2& a = message->typeCast<Acceleration2>();
       }
     } 
     catch (const IOException& e) {
       ROS_WARN_STREAM("IOException: " << e.what());
       ROS_WARN_STREAM("Retrying in " << _retryTimeout << " [s]");
       timer.sleep(_retryTimeout);
     }
     _updater.update();
     ros::spinOnce();
   }
 }