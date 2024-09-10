 bool handle_response() {
   auto response = socket.recv_all(0).front().str();
   logging::DEBUG(uuid + ":" + response.substr(0, 1));
   switch(response.front()) {
     case 'I': //INFO for the camera
       socket.send(std::string("N"), ZMQ_DONTWAIT);
       settings = response.substr(1);
       return true;
     case 'N': //NEXT camera image name
       next = response.substr(1);
       if(next.size())
         socket.send(std::string("C" + next), ZMQ_DONTWAIT);
       break;
     case 'W': //WAIT so many seconds before asking again
       settings = response.substr(1);
       wait_until = std::time(nullptr) + 1; //TODO: parse out the interval
       return true;
     case 'C': //CAMERA image data is here
       {
         auto destination = www_dir + "/cameras/" + uuid + "/" + next.substr(next.front() == '/' ? 1 : 0);
         auto db = www_dir + "/cameras/" + uuid + ".db";
         if(!system(("mkdir -p $(dirname " + destination + ")").c_str())) {
           std::fstream output(destination, std::ios::out | std::ios::binary | std::ios::trunc);
           output.write(response.data() + 1, response.size() - 1);
           update_record(db, destination);
           photo_count = record_count(db);
           logging::INFO("Wrote " + destination);
         }
       }
       socket.send(std::string("D" + next), ZMQ_DONTWAIT);
       next = "";
       break;
     case 'E': //ERROR came in
       settings = next = "";
       wait_until = std::time(nullptr) + 1;
       break;
     default:
       logging::WARN("Unrecognized response: " + response);
       break;
   }
   return false;
 }