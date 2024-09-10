void FractalVis::drawFrame(sf::Texture& screen) {
    frame.create(256, 256, &(*colors1DUint8)); //set the Image frame to the known display array
    frame.setPixel(128, 128, sf::Color::Yellow); //put a dot in the center
    screen.loadFromImage(frame); //display the image
};