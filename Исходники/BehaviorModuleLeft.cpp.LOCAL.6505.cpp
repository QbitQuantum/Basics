void BehaviorModule::getArmDependentOptions(Bottle &b, Vector &_gOrien,
					    Vector &_gDisp, Vector &_dOffs, Vector &_dLift, Vector &_home_x) {
  if (Bottle *pB=b.find("grasp_orientation").asList()) {
    int sz = pB->size();
    int len = _gOrien.length();
    int l = len < sz ? len : sz;

    for (int i = 0; i < l; i++)
      _gOrien[i] = pB->get(i).asDouble();
  }

  if (Bottle *pB=b.find("grasp_displacement").asList()) {
    int sz = pB->size();
    int len = _gDisp.length();
    int l = len < sz ? len : sz;

    for (int i = 0; i < l; i++)
      _gDisp[i] = pB->get(i).asDouble();
  }

  if (Bottle *pB=b.find("systematic_error_displacement").asList()) {
    int sz = pB->size();
    int len = _dOffs.length();
    int l = len < sz ? len : sz;

    for (int i = 0; i < l; i++)
      _dOffs[i] = pB->get(i).asDouble();
  }

  if (Bottle *pB=b.find("lifting_displacement").asList()) {
    int sz = pB->size();
    int len = _dLift.length();
    int l = len < sz ? len : sz;

    for (int i = 0; i < l; i++)
      _dLift[i] = pB->get(i).asDouble();
  }

  if (Bottle *pB=b.find("home_position").asList()) {
    int sz = pB->size();
    int len = _home_x.length();
    int l = len < sz ? len : sz;

    for (int i = 0; i < l; i++)
      _home_x[i] = pB->get(i).asDouble();
  }
}