void ConnectionHandler::SendResponse(Reply* reply)
{
	for (size_t i = 0; i < reply->headers.size(); i++)
	{
		char * line = reply->headers.at(i);

		boost::asio::async_write(socket_,
			boost::asio::buffer(line, strnlen_s(line, 512)),
			boost::bind(&ConnectionHandler::HandleWrite, this, boost::asio::placeholders::error));
	}
	if (reply->text_content)
	{
		char* line = reply->text_content;

		boost::asio::async_write(socket_,
			boost::asio::buffer(line, strnlen_s(line, 2048)),
			boost::bind(&ConnectionHandler::HandleWrite, this, boost::asio::placeholders::error));
	}
	else if (reply->file_location)
	{
		boost::system::error_code write_error;
		// send file as binary data
		// // load file (binary) and set possition at the end of file
		std::ifstream source_file(reply->file_location, std::ios_base::binary | std::ios_base::ate);
		if (source_file)
		{
			char file_buffer[8192]; //TODO 8192 should be const / Buffersize of 8192 is efficient, because it equals 1 or 2 disk blocks 
			size_t file_size = source_file.tellg();
			//set pointer to start of file
			source_file.seekg(0);

			while (true)
			{
				if (!source_file.eof()) //if -> pointer not at end of file
				{
					source_file.read(file_buffer, 8192); //TODO 1024 should be const
					if (source_file.gcount() <= 0) // if -> amount of bytes read <= 0
						cout << "Read file error" << endl;
					boost::asio::write(socket_, boost::asio::buffer(file_buffer, source_file.gcount()), boost::asio::transfer_all(), write_error);
					if (write_error)
						cout << "Socket write error" << endl;
				}
				else 
				{
					break;
				}
			}
			cout << "send file went successfull" << endl;
		}
	}
}