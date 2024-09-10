// Load the sounds used in the game
void JukeBox::loadSounds() {
	if (!boarderSoundBuffer.loadFromFile("resources/unclick.wav")) __nop();
	boarderSound.setBuffer(boarderSoundBuffer);

	if (!paddleSoundBuffer.loadFromFile("resources/menu1.wav")) __nop();
	paddleSound.setBuffer(paddleSoundBuffer);

	if (!scoreSoundBuffer.loadFromFile("resources/launch_deny2.wav")) __nop();
	scoreSound.setBuffer(scoreSoundBuffer);
}