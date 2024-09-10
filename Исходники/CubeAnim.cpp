bool		CubeAnim::makeCube(const int x, const int y, const int z)
{
  AObject	*cube = create<Cube>();
  std::pair<float, float> pos;

  cube->setType(BLOCKD);
  if (cube->initialize() == false)
    return (false);
  pos = std::make_pair(x, z);
  cube->setPos(pos);
  _objects.push_back(cube);
  return (true);
}