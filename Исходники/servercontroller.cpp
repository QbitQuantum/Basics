void ServerController::getReviewers(sf::Packet &packet, sf::TcpSocket &client)
{
	sf::Packet response;
	std::string username, conference;
	std::vector<std::string> reviewer;
	
	packet >> username >> conference;	

	int confIndex = checkConference(conference);
	if(confIndex == -1)
	{
		return;
	}
	data.conferences[confIndex].getReviewers(reviewer);
	
	response << (int)reviewer.size();
	
	for (int i = 0; i < (int)reviewer.size(); i++)
	{
		response << reviewer[i];
	}
	
	client.send(response);
}