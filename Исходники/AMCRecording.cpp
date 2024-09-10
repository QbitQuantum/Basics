ASFSkeleton::JointQuats ASFSkeleton::computeSkelStateQuaternions() const {
  JointQuats qs;
  using J = Skeleton::JointType;
  const auto p = [&] (const J& iJoint) {
    const string& boneName = kKinectBones2ASFBones.at(iJoint);
    const int bIdx = name2idx(boneName.c_str());
    const Bone& b = *getBone(getRoot(), bIdx);
    const Vec3f bpBody = m_pRootBone->parent2local * b.tgt_pos;
    return bpBody;
  };
  const Vec3f
    // canonical ASFSkeleton frame is x-left, y-up, z-forward
    up = Vec3f::UnitY(),
    right = -Vec3f::UnitX(),
    /// TORSO ///
    // spine base canonical frame
    yb = up,                                    // pelvic up
    xb = crossNorm(yb, right),                  // pelvic front
    zb = crossNorm(xb, yb),                     // pelvic right

    // pelvis frame - origin = ow, child = ove
    ove = p(J::JointType_SpineMid),             // mid-spine vertebrae
    yp = (ove - p(J::JointType_SpineBase)).normalized(),    // pelvic up
    xp = crossNorm(yp, right),                  // pelvic front
    zp = crossNorm(xp, yp),                     // pelvic right

    // torso frame - origin = ove, child = osc
    osc = p(J::JointType_SpineShoulder),        // sternoclavicular joint
    yto = (osc - ove).normalized(),             // torso up
    xto = crossNorm(yto, right),                // torso front
    zto = crossNorm(xto, yto),                  // torso right

    // shoulder-mid frame - origin = osc, child = ocv
    ocv = p(J::JointType_Neck),                 // cervical vertebrae (neck)
    ysh = (ocv - osc).normalized(),             // shoulder-mid up
    xsh = crossNorm(ysh, right),                // shoulder-mid front
    zsh = crossNorm(xsh, ysh),                  // shoulder-mid right

    // neck frame - origin = ocv, child = ohe
    zne = zp,                                   // neck right
   _xne = crossNorm(ysh, zne),                  // neck front temporary
    yne = crossNorm(zne, _xne),                 // neck up
    xne = crossNorm(yne, zne),                  // neck front

    // L clavicle frame - origin osc, child = ghl
    ghl = p(J::JointType_ShoulderLeft),         // glenohumeral rotation center L
    zcl = -(ghl - osc).normalized(),            // clavicle right L
    xcl = crossNorm(ysh, zcl),                  // clavicle front L
    ycl = crossNorm(zcl, xcl),                  // clavicle up L

    // R clavicle frame - origin osc, child = ghr
    ghr = p(J::JointType_ShoulderRight),        // glenohumeral rotation center R
    zcr = (ghr - osc).normalized(),             // clavicle right R
    xcr = crossNorm(ysh, zcr),                  // clavicle front R
    ycr = crossNorm(zcr, xcr),                  // clavicle up R

    /// ARMS AND HANDS ///

    // L arm frame common
    ecl = p(J::JointType_ElbowLeft),            // epicondyle L
    yhl = (ghl - ecl).normalized(),             // humerus up L
    scl = p(J::JointType_WristLeft),            // radial+ulnar styloid L
    yfl = (ecl - scl).normalized(),             // forearm up L

    // L humerus frame - origin = ghl, child = ecl
    // yhl computed in common arm frame
    _zhl = crossNorm(yfl, yhl),
    zhl = (_zhl.dot(right) > 0) ? _zhl : -_zhl, // humerus right L
    xhl = crossNorm(yhl, zhl),                  // humerus front L
    // TODO(MS): degenerate case: yhl-yfl parallel

    // L forearm frame - origin = scl, child = ecl
    // yfl computed in common arm frame
    zfl = zhl,                                  // forearm right L
    xfl = crossNorm(yfl, zfl),                  // forearm front L

    // L palm frame - origin = scl, child = pal
    xrl = xfl,                                  // trapezium front L
    yrl = yfl,                                  // trapezium up L
    zrl = zfl,                                  // trapezium right L

    // L thumb frame - origin = pal, child = thl
    xxl = xfl,                                  // thumb front L
    yxl = yfl,                                  // thumb up L
    zxl = zfl,                                  // thumb right L

    // L fingertip frame - origin = pal, child = phl
    xpl = xfl,                                  // distal phalanges front L
    zpl = zfl,                                  // distal phalanges right L
    ypl = yfl,                                  // distal phalanges up L

    // R arm frame common
    ecr = p(J::JointType_ElbowRight),           // epicondyle R
    yhr = (ghr - ecr).normalized(),             // humerus up R
    scr = p(J::JointType_WristRight),           // radial+ulnar styloid R
    yfr = (ecr - scr).normalized(),             // forearm up R

    // R humerus frame - origin = ghr, child = ecr
    // yhl computed in common arm frame
    _zhr = crossNorm(yfr, yhr),
    zhr = (_zhr.dot(right) > 0) ? _zhr : -_zhr, // humerus right R
    xhr = crossNorm(yhr, zhr),                  // humerus front R
    // TODO(MS): degenerate case: yhr-yfr parallel

    // R forearm frame - origin = scr, child = ecr
    // yfl computed in common arm frame
    zfr = zhr,                                  // forearm right R
    xfr = crossNorm(yfr, zfr),                  // forearm front R

    // R palm frame - origin = scr, child = par
    xrr = xfr,                                  // trapezium front R
    yrr = yfr,                                  // trapezium up R
    zrr = zfr,                                  // trapezium right R

    // R thumb frame - origin = par, child = thr
    xxr = xfr,                                  // thumb front R
    yxr = yfr,                                  // thumb up R
    zxr = zfr,                                  // thumb right R

    // R fingertip frame - origin = par, child = thr
    xpr = xfr,                                  // distal phalanges front R
    zpr = zfr,                                  // distal phalanges right R
    ypr = yfr,                                  // distal phalanges up R

    /// LEGS AND FEET ///

    // L ilium/hip - origin = ove, child = fhl
    fhl = p(J::JointType_HipLeft),              // hip femur head L
    zil = -fhl.normalized(),                    // ilium/hip right L
    xil = crossNorm(yp, zil),                   // ilium/hip front L
    yil = crossNorm(zil, xil),                  // ilium/hip up L

    // L thigh - origin = fhl, child = otl
    otl = p(J::JointType_KneeLeft),             // knee L
    ytl = (fhl - otl).normalized(),             // thigh up L
    xtl = crossNorm(ytl, right),                // thigh front L
    ztl = crossNorm(xtl, ytl),                  // thigh right L

    // L shank - origin = otl, child osl
    osl = p(J::JointType_AnkleLeft),            // ankle L
    ysl = (otl - osl).normalized(),             // shank up L
    xsl = crossNorm(ysl, right),                // shank front L
    zsl = crossNorm(xsl, ysl),                  // shank right L

    // L foot
    yml = -xsl,                                 // foot toe up L
    zml = zsl,                                  // foot toe right L
    xml = crossNorm(yml, zml),                  // foot toe front L

    // R ilium/hip - origin = ove, child = fhr
    fhr = p(J::JointType_HipRight),             // hip femur head R
    zir = fhr.normalized(),                     // ilium/hip right R
    xir = crossNorm(yp, zir),                   // ilium/hip front R
    yir = crossNorm(zir, xir),                  // ilium/hip up R

    // R thigh - origin = fhr, child = otr
    otr = p(J::JointType_KneeRight),            // knee R
    ytr = (fhr - otr).normalized(),             // thigh up R
    xtr = crossNorm(ytr, right),                // thigh front R
    ztr = crossNorm(xtr, ytr),                  // thigh right R
 
    // R shank - origin = otr, child osr
    osr = p(J::JointType_AnkleRight),           // ankle R
    ysr = (otr - osr).normalized(),             // shank up R
    xsr = crossNorm(ysr, right),                // shank front R
    zsr = crossNorm(xsr, ysr),                  // shank right R

    // R foot
    ymr = -xsr,                                 // foot toe up R
    zmr = zsr,                                  // foot toe right R
    xmr = crossNorm(ymr, zmr);                  // foot toe front R

  qs[J::JointType_SpineBase]      = Rquat(xb,  yb,  zb),   // base
  qs[J::JointType_SpineMid]       = Rquat(xp,  yp,  zp),   // pelvis
  qs[J::JointType_SpineShoulder]  = Rquat(xto, yto, zto),  // torso
  qs[J::JointType_Neck]           = Rquat(xsh, ysh, zsh),  // neck
  qs[J::JointType_Head]           = Rquat(xne, yne, zne),  // head
  qs[J::JointType_ShoulderLeft]   = Rquat(xcl, ycl, zcl),  // clavicle L
  qs[J::JointType_ShoulderRight]  = Rquat(xcr, ycr, zcr),  // clavicle R
  qs[J::JointType_ElbowLeft]      = Rquat(xhl, yhl, zhl),  // humerus L
  qs[J::JointType_WristLeft]      = Rquat(xfl, yfl, zfl),  // forearm L
  qs[J::JointType_HandLeft]       = Rquat(xrl, yrl, zrl),  // trapezium L
  qs[J::JointType_ThumbLeft]      = Rquat(xxl, yxl, zxl),  // thumb L
  qs[J::JointType_HandTipLeft]    = Rquat(xpl, ypl, zpl),  // hand tips L
  qs[J::JointType_ElbowRight]     = Rquat(xhr, yhr, zhr),  // humerus R
  qs[J::JointType_WristRight]     = Rquat(xfr, yfr, zfr),  // forearm R
  qs[J::JointType_HandRight]      = Rquat(xrr, yrr, zrr),  // trapezium R
  qs[J::JointType_ThumbRight]     = Rquat(xxr, yxr, zxr),  // thumb R
  qs[J::JointType_HandTipRight]   = Rquat(xpr, ypr, zpr),  // hand tips R
  qs[J::JointType_HipLeft]        = Rquat(xil, yil, zil),  // hip L
  qs[J::JointType_KneeLeft]       = Rquat(xtl, ytl, ztl),  // thigh L
  qs[J::JointType_AnkleLeft]      = Rquat(xsl, ysl, zsl),  // shank L
  qs[J::JointType_FootLeft]       = Rquat(xml, yml, zml),  // foot L
  qs[J::JointType_HipRight]       = Rquat(xir, yir, zir),  // hip R
  qs[J::JointType_KneeRight]      = Rquat(xtr, ytr, ztr),  // thigh R
  qs[J::JointType_AnkleRight]     = Rquat(xsr, ysr, zsr),  // shank R
  qs[J::JointType_FootRight]      = Rquat(xmr, ymr, zmr);  // foot R

  for (int i = 0; i < Skeleton::kNumJoints; ++i) {
    const J ji = static_cast<J>(i);
    const int bIdx = name2idx(kKinectBones2ASFBones.at(ji).c_str());
    const Bone& b = *getBone(getRoot(), bIdx);
    qs[i] = b.local2world.inverse() * qs[i];
  }

  return qs;
}