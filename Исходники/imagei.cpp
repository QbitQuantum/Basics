 void ReplyTask::run() {
   jderobot::ImageDataPtr reply(new jderobot::ImageData);
   ::jderobot::Time t;
   while (1) {
     IceUtil::Time t = IceUtil::Time::now();
     reply->timeStamp.seconds = (long) t.toSeconds();
     reply->timeStamp.useconds = (long) t.toMicroSeconds()
         - reply->timeStamp.seconds * 1000000;
     {  //critical region start
       IceUtil::Mutex::Lock sync(requestsMutex);
       while (!requests.empty()) {
         jderobot::AMD_ImageProvider_getImageDataPtr cb = requests.front();
         requests.pop_front();
         cb->ice_response(reply);
       }
     }
   }
 }