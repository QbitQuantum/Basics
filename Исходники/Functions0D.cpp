  Vec2f VertexOrientation2DF0D::operator()(Interface0DIterator& iter) {
    Vec2f A,C;
    Vec2f B(iter->getProjectedX(), iter->getProjectedY());
    if(iter.isBegin())
      A = Vec2f(iter->getProjectedX(), iter->getProjectedY());
    else
      {
	Interface0DIterator previous = iter;
	--previous ;
	A = Vec2f(previous->getProjectedX(), previous->getProjectedY());
      }
    Interface0DIterator next = iter;
    ++next ;
    if(next.isEnd())
      C = Vec2f(iter->getProjectedX(), iter->getProjectedY());
    else
      C = Vec2f(next->getProjectedX(), next->getProjectedY());

    Vec2f AB(B-A);
    if(AB.norm() != 0)
      AB.normalize();
    Vec2f BC(C-B);
    if(BC.norm() != 0)
      BC.normalize();
    Vec2f res (AB + BC);
    if(res.norm() != 0)
      res.normalize();
    return res;
  }