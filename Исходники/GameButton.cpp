void			GameButton::update(gdl::Clock & clock, Scene *scene)
{
  (void)scene;
  if (this->_current)
    this->rotate(glm::vec3(1, 0, 0), (50 * clock.getElapsed()));
}