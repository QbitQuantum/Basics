 /*! Outgoing messages conform to the sam format as incoming mssages,
     i.e., they have 4 header parts and a data part.
 */
 static int send_multipart(socket_t& socket,
                    const std::string& name,
                    const std::string& device,
                    const std::string& desc,
                    const std::string& data,
                    int flags = 0)
 {
     message_t msg;
     str_to_msg(name, msg);
     socket.send(msg, ZMQ_SNDMORE);
     str_to_msg(device, msg);
     socket.send(msg, ZMQ_SNDMORE);
     str_to_msg(desc, msg);
     socket.send(msg, ZMQ_SNDMORE);
     str_to_msg(data, msg);
     socket.send(msg);
            
     return 4;
 }