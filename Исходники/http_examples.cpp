 static void read_and_send(const shared_ptr<HttpServer::Response> &response, const shared_ptr<ifstream> &ifs) {
   // Read and send 128 KB at a time
   static vector<char> buffer(131072); // Safe when server is running on one thread
   streamsize read_length;
   if((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) > 0) {
     response->write(&buffer[0], read_length);
     if(read_length == static_cast<streamsize>(buffer.size())) {
       response->send([response, ifs](const SimpleWeb::error_code &ec) {
         if(!ec)
           read_and_send(response, ifs);
         else
           cerr << "Connection interrupted" << endl;
       });
     }
   }
 }