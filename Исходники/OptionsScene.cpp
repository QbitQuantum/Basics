// We  initialize our instance
bool OptionsScene::init() {
	// 1. super init first
	if (!Layer::init()) { // if there is a mistake then we terminate the program, it couldnt launch
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// add a label shows "Creditos" create and initialize labels

	auto labelTitulo = LabelTTF::create("Opciones", "Tahoma", 32);

	// position the label on the upper center of the screen
	labelTitulo->setPosition(Point(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * .88f));

	// add the label as a child to this layer
	this->addChild(labelTitulo, 1);

	// We add the devs labels
	this->showNames(origin, visibleSize);

	// Creates the background of the game menu.
	auto sprite = Sprite::create("GameMenu/0000.jpg"); // sprites are important, those are the images
	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	createMenu(); // We bring to live this scene.

	// Reproducir la musica de la seleccion del nivel: quiza sea mejor dejar la misma del menu
	// principal y cambiarla cuando se haya iniciado el nivel. Se deja aqui por propositos
	// ilustrativos
	auto sound = CocosDenshion::SimpleAudioEngine::getInstance();
	sound->stopBackgroundMusic(); // this steps are to change tracks.
	sound->playBackgroundMusic("Music/Options.mp3", true); // We use a piece of music we already have and reproduce it for the options scene.

	return true; // we managed to bring frankestein alive, I mean, the game.
}