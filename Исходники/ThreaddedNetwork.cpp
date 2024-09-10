void ThreaddedNetwork::inThreadUpdate()
{ 
  std::string currentMessage = "";
  char buffer[RCVBUFSIZE];
  int recvMsgSize;
  bool hasStart = false;
  while(true)
  {
    TCPSocket* sock = m_servSock.accept();
    std::cout <<"Got Connection\n";
    recvMsgSize = 1; // set to one just so we enter the loop
    while(recvMsgSize > 0)
    {
      // clear the input buffer
      memset(buffer, 0, RCVBUFSIZE);
      // get data from the socket
      recvMsgSize = sock->recv(buffer, RCVBUFSIZE);
      std::cout << "msg: ";
      std::cout << buffer << "\n";
      // iterate over the recieved data
      for(int i=0; i<recvMsgSize; i++)
      {
        // if we're recording a message
        if(hasStart)
        {
          // if this is the end of the message
          if(buffer[i] == ']')
          {
            // send the message to the main thread
            q_new_messages.push(currentMessage);
            // stop recording messages
            hasStart = false;
          }
          // if this is not the end of the message
          else
          {
            // add this character to the end of the current messsage
            currentMessage += buffer[i];
          }
        }
        // if we recieve a new start character
        if(buffer[i] == '[')
        {
          // start recording
          hasStart = true;
          // reset the current message
          currentMessage = "";
        } // end if
      } // end for
      //sock->send(buffer,recvMsgSize);
      std::string outgoing = "";
      for(int i=0; i<q_outgoing_messages.size(); i++)
      {
        outgoing += "[";
        outgoing += q_outgoing_messages.at(i);
        outgoing += "]";
      }
      std::cout << "outgoing:\n" << outgoing << "\n";
      sock->send("[Good]",6);
      if(outgoing.length() > 0)
      {
        sock->send(outgoing.c_str(), outgoing.length());
      }
      sock->send("\n",1);
      std::cout << "Closing connection\n";
    } // end while
    delete sock;
  } // end while
} // end inThreadUpdate