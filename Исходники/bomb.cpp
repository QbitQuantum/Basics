void Bomb::show(gdl::AShader &shader, gdl::Clock &clock)
{
  this->model.draw(shader, this->getTransformation(), clock.getElapsed());
}