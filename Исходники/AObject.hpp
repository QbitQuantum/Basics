 virtual void draw(gdl::AShader &shader, gdl::Clock const &clock)
 {
   (void)clock;
   // On bind la texture pour dire que l'on veux l'utiliser
   // Et on dessine notre cube
   // std::cout << static_cast<float>(clock.getElapsed()) * _speed << std::endl;
   // std::cout << "pos x: " << _position.x <<  " pos y: " << _position.y <<  "pos z: " << _position.z << std::endl;
   // std::cout << _rotation << std::endl;
   this->bomberman.draw(shader, getTransformation(), static_cast<float>(clock.getElapsed()));
 }