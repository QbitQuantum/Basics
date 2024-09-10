int main() {

	srand(time(NULL));

	Screen screen;
	Swarm swarm;

	if (!screen.init()) {
		cout << "Error initializing SDL" << flush;
	}

	while (true) {

		const Particle* const pParticles = swarm.getParticles();

		screen.clear();
		swarm.update();

		int elapsed = SDL_GetTicks();
		unsigned char green = (unsigned char) (1 + sin(elapsed * 0.001) * 128);
		unsigned char red = (unsigned char) (1 + sin(elapsed * 0.002) * 128);
		unsigned char blue = (unsigned char) (1 + sin(elapsed * 0.003) * 128);

//		unsigned char blue = 255;
//		unsigned char red = 255;
//		unsigned char green = 255;

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2
					+ Screen::SCREEN_HEIGHT / 2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.screenUpdate();

		if (!screen.processEvents()) {
			break;
		}
	}

	screen.close();

	return 0;
}