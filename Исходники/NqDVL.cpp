 bool NqDVL::start(bool debug)
 {
   _debug = debug;
   openPort();
   if(isOpen())
     {
       ros::NodeHandle n;
       _timer = n.createTimer(ros::Duration(1.0/_freq),&NqDVL::timerCallBack,this);
     }
   else
     {
       return false;
     }
 }