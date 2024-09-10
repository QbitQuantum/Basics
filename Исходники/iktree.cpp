void IKTree::solveJoint(int frame, int i, IKEffectorList &effList)
{
  double x, y, z;
  double ang = 0;

  MT_Quaternion q;
  MT_Quaternion totalPosRot = MT_Quaternion(0,0,0,0);
  MT_Quaternion totalDirRot = MT_Quaternion(0,0,0,0);
  MT_Vector3 axis(0,0,0);
  BVHNode *n;
  int numPosRot = 0, numDirRot = 0;

  if (bone[i].numChildren == 0) {     // reached end site
    if (bone[i].node->ikOn) {
      effList.index[effList.num++] = i;
    }
    return;
  }

  for (int j=0; j<bone[i].numChildren; j++) {
    IKEffectorList el;
    el.num = 0;
    solveJoint(frame, bone[i].child[j], el);
    for (int k=0; k<el.num; k++) {
      effList.index[effList.num++] = el.index[k];
    }
  }

  updateBones(i);

  for (int j=0; j<effList.num; j++) {
    int effIndex = effList.index[j];
    n = bone[effIndex].node;
    MT_Vector3 effGoalPos(n->ikGoalPos[0],
			  n->ikGoalPos[1],
			  n->ikGoalPos[2]);
    const MT_Vector3 pC =
      (bone[effIndex].pos - bone[i].pos).safe_normalized();
    const MT_Vector3 pD =
      (effGoalPos - bone[i].pos).safe_normalized();
    MT_Vector3 rotAxis = pC.cross(pD);
    if (rotAxis.length2() > MT_EPSILON) {
      totalPosRot += MT_Quaternion(rotAxis, bone[i].weight * acos(pC.dot(pD)));
      numPosRot++;
    }

    const MT_Vector3 uC =
      (bone[effIndex].pos - bone[effIndex-1].pos).safe_normalized();
    const MT_Vector3 uD =
      (MT_Vector3(n->ikGoalDir[0], n->ikGoalDir[1], n->ikGoalDir[2])).safe_normalized();
    rotAxis = uC.cross(uD);
    if (rotAxis.length2() > MT_EPSILON) {
      double weight = 0.0;
      if (i == effIndex-1) weight = 0.5;
      totalDirRot += MT_Quaternion(rotAxis, weight * acos(uC.dot(uD)));
      numDirRot++;
    }
  }

  if ((numPosRot + numDirRot) > MT_EPSILON) {
    n = bone[i].node;
    n->ikOn = true;
    // average the quaternions from all effectors
    if (numPosRot)
      totalPosRot /= numPosRot;
    else
      totalPosRot = identity;
    if (numDirRot)
      totalDirRot /= numDirRot;
    else
      totalDirRot = identity;
    MT_Quaternion targetRot = 0.9 * totalPosRot + 0.1 * totalDirRot;
    targetRot = targetRot * bone[i].lRot;
    toEuler(targetRot, n->channelOrder, x, y, z);
    if (jointLimits) {
      bone[i].lRot = identity;
      for (int k=0; k<n->numChannels; k++) {  // clamp each axis in order
        switch (n->channelType[k]) {
          case BVH_XROT: ang = x; axis = xAxis; break;
          case BVH_YROT: ang = y; axis = yAxis; break;
          case BVH_ZROT: ang = z; axis = zAxis; break;
          default: break;
        }
        // null axis leads to crash in q.setRotation(), so check first
        if(axis.length())
        {
          if (ang < n->channelMin[k]) ang = n->channelMin[k];
          else if (ang > n->channelMax[k]) ang = n->channelMax[k];
          q.setRotation(axis, ang * M_PI / 180);
          bone[i].lRot = q * bone[i].lRot;
        }
      }
    }
    else
      bone[i].lRot = targetRot;
  }
}