bool Reciever::uploadingFileOperation(Socket& socket,std::string string_, std::string command_, int content, std::string fileName_, int port, std::string category)
{
	Message m;
	std::string path = "";
	const int BufLen = 1024;//buffer size
	Socket::byte buffer[BufLen];
	bool ok = false, flag = false, ostreamFlag = true;
	std::ofstream* outfile = nullptr;
	while (true)
	{
		if (flag == true)//if the some part of buffer from binary file is yet to be received then get the commands again
		{
			string_ = socket.recvString();
			std::vector<std::string> vec_ = m.splitting(string_, '\n');
			std::map<std::string, std::string> map_ = m.makeMap(vec_);
			command_ = map_["Command"];
			fileName_ = map_["FileName"];
			content = stoi(map_["BodyContentLength"]);
			port = stoi(map_["SourcePort"]);
			category = map_["Category"];
		}
		if (ostreamFlag)
		{
			path = setPath(command_, category,fileName_);
			outfile = new std::ofstream;
			outfile->open(path, std::ios::out | std::ios::binary);//opens the file in binary mode
			ostreamFlag = false;
		}
		ok = socket.recv(content, buffer);
		if (command_ == "1" || command_ == "11")//if the buffer from binary file is coming for last time
		{
			outfile->write(buffer, content);
			outfile->close();
			return true;
		}
		outfile->write(buffer, content);//writing into file
		if (socket == INVALID_SOCKET || !ok)//if the string is not received properly of socket is invalid then break
			return false;
		flag = true;
	}
	return true;
}