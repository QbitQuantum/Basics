void HangupMessage::handle(Game &game, Message &message) {
	cout << "received hangup message" << endl;

	game.setWon(true);
	game.exit();
}