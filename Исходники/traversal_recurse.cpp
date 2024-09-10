void collisionRecurse(MeshCollisionTraversalNodeOBB* node, int b1, int b2, const Matrix3f& R, const Vec3f& T, BVHFrontList* front_list)
{
  bool l1 = node->isFirstNodeLeaf(b1);
  bool l2 = node->isSecondNodeLeaf(b2);

  if(l1 && l2)
  {
    updateFrontList(front_list, b1, b2);

    if(node->BVTesting(b1, b2, R, T)) return;

    node->leafTesting(b1, b2, R, T);
    return;
  }

  if(node->BVTesting(b1, b2, R, T))
  {
    updateFrontList(front_list, b1, b2);
    return;
  }

  Vec3f temp;

  if(node->firstOverSecond(b1, b2))
  {
    int c1 = node->getFirstLeftChild(b1);
    int c2 = node->getFirstRightChild(b1);

    const OBB& bv1 = node->model1->getBV(c1).bv;

    Matrix3f Rc(R.transposeTimes(bv1.axis[0]), R.transposeTimes(bv1.axis[1]), R.transposeTimes(bv1.axis[2]));
    temp = T - bv1.To;
    Vec3f Tc(temp.dot(bv1.axis[0]), temp.dot(bv1.axis[1]), temp.dot(bv1.axis[2]));

    collisionRecurse(node, c1, b2, Rc, Tc, front_list);

    // early stop is disabled is front_list is used
    if(node->canStop() && !front_list) return;

    const OBB& bv2 = node->model1->getBV(c2).bv;

    Rc = Matrix3f(R.transposeTimes(bv2.axis[0]), R.transposeTimes(bv2.axis[1]), R.transposeTimes(bv2.axis[2]));
    temp = T - bv2.To;
    Tc.setValue(temp.dot(bv2.axis[0]), temp.dot(bv2.axis[1]), temp.dot(bv2.axis[2]));

    collisionRecurse(node, c2, b2, Rc, Tc, front_list);
  }
  else
  {
    int c1 = node->getSecondLeftChild(b2);
    int c2 = node->getSecondRightChild(b2);

    const OBB& bv1 = node->model2->getBV(c1).bv;
    Matrix3f Rc;
    temp = R * bv1.axis[0];
    Rc(0, 0) = temp[0]; Rc(1, 0) = temp[1]; Rc(2, 0) = temp[2];
    temp = R * bv1.axis[1];
    Rc(0, 1) = temp[0]; Rc(1, 1) = temp[1]; Rc(2, 1) = temp[2];
    temp = R * bv1.axis[2];
    Rc(0, 2) = temp[0]; Rc(1, 2) = temp[1]; Rc(2, 2) = temp[2];
    Vec3f Tc = R * bv1.To + T;

    collisionRecurse(node, b1, c1, Rc, Tc, front_list);

    // early stop is disabled is front_list is used
    if(node->canStop() && !front_list) return;

    const OBB& bv2 = node->model2->getBV(c2).bv;
    temp = R * bv2.axis[0];
    Rc(0, 0) = temp[0]; Rc(1, 0) = temp[1]; Rc(2, 0) = temp[2];
    temp = R * bv2.axis[1];
    Rc(0, 1) = temp[0]; Rc(1, 1) = temp[1]; Rc(2, 1) = temp[2];
    temp = R * bv2.axis[2];
    Rc(0, 2) = temp[0]; Rc(1, 2) = temp[1]; Rc(2, 2) = temp[2];
    Tc = R * bv2.To + T;

    collisionRecurse(node, b1, c2, Rc, Tc, front_list);
  }
}