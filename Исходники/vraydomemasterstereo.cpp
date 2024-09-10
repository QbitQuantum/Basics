void VRayCamera::getTM(TimeValue t, INode *node, ViewExp *vpt, Matrix3 &tm) {
  tm=node->GetObjectTM(t);

  AffineParts ap;
  decomp_affine(tm, &ap);
  tm.IdentityMatrix();
  tm.SetRotate(ap.q);
  tm.SetTrans(ap.t);

  float scaleFactor=vpt->NonScalingObjectSize()*vpt->GetVPWorldWidth(tm.GetTrans())/360.0f;
  tm.Scale(Point3(scaleFactor,scaleFactor,scaleFactor));
}