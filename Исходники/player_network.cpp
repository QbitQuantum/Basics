void Player::receiveMessage() {
	ClientMessage inMessage = network->popMessage();
	if(inMessage.first == "go")
		startGame = true;
	else if(inMessage.first == "connectDummy")
		return;
	else if(inMessage.first != "")
		translateMessage(inMessage);
}