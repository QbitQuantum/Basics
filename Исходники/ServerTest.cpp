void ClientHandler::operator()(Socket& socket_)
{
	Display *disp = new Display();
	BlockingQueue<string> q_;
			while (true)
			{
				Receiver *rs = new Receiver();
				std::string command = socket_.recvString();
				q_.enQ(command);
				if (command.size() == 0)
					break;
				size_t size= q_.size();
				string ackmsg;
				for (size_t i = 0; i < size; i++)
				{
					command = q_.deQ();
					ackmsg = rs->start(command, socket_);
				}
				Sender *s = new Sender();
				if (ackmsg != "")
				{
					s->sendAck(socket_, ackmsg);
				}
		}
  
  disp->show("ClientHandler socket connection closing");
  socket_.shutDown();
  socket_.close();
  disp->show("ClientHandler thread terminating");

}