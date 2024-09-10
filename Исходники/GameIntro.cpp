int	Intro::GameIntro::update(gdl::Clock const& clock, gdl::Input &input)
{
  _introtime -= clock.getElapsed();
  if (_cam->getLookAt().y - clock.getElapsed() * 10 > 0)
    _cam->getLookAt().y -= clock.getElapsed() * 10;
  _cam->getCameraDiff().z += clock.getElapsed() * 5;
  if (_introtime <= 0 || input.getKey(SDLK_SPACE))
    return (0);
  return (4);
}