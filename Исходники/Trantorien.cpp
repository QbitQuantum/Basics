void		Trantorien::draw(t_player *tmp, gdl::AShader &shader, gdl::Clock const &clock)
{
  tmp->time += clock.getElapsed();
  // Set la position
  _position = glm::vec3(tmp->x + 1.5, 0.5, tmp->y + 1.5);
  _scale = glm::vec3(tmp->l / 2.0f, tmp->l / 2.0f, tmp->l / 2.0f);
  
  // set L'orientation
  _orient = getOrient(_posCam);
  float		angle;
  angle  = scalaire(glm::vec2(0, 1), glm::vec2(_position.z - _posCam.z,
					       _position.x - _posCam.x));
  if (_position.z < _posCam.z)
    rotate(glm::vec3(0, 1, 0), (angle) * 180 / PI);
  else
    rotate(glm::vec3(0, -1, 0), (angle) * 180 / PI);
  int a = _orient + tmp->o;
  if (a > 4)
    a -= 4;
  // Set l'animation
  if (tmp->anime > _nb_anime - 1)
    tmp->anime = 0;
  // Bind la texture et draw
  (void)clock;
  _geometry[a - 1][tmp->anime].draw(shader, getTransformation(), GL_QUADS);
  _rotation = glm::vec3(0, 0, 0);
}