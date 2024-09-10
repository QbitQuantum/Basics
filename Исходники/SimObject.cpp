void SimObject::setPosition(const Vector3d& pos)
{
  Vector3d translation(pos);
  translation -= position;
  position = pos;
  ObjectList::const_iterator listPos;
  for(listPos = childNodes.begin(); listPos != childNodes.end(); ++listPos)
  {
    (*listPos)->translate(translation);
  }
}