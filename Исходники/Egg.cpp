void	Egg::draw(gdl::AShader& shader, gdl::Clock const & clock)
{
  _model->draw(shader, getTransformation(), clock.getElapsed());
}