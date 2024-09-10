  void Torsion::calcForce(RealType& angle, bool doParticlePot) {

    Vector3d pos1 = atoms_[0]->getPos();
    Vector3d pos2 = atoms_[1]->getPos();
    Vector3d pos3 = atoms_[2]->getPos();
    Vector3d pos4 = atoms_[3]->getPos();

    Vector3d r21 = pos1 - pos2;
    Vector3d r32 = pos2 - pos3;
    Vector3d r43 = pos3 - pos4;

    //  Calculate the cross products and distances
    Vector3d A = cross(r21, r32);
    RealType rA = A.length();
    Vector3d B = cross(r32, r43);
    RealType rB = B.length();

    /* 
       If either of the two cross product vectors is tiny, that means
       the three atoms involved are colinear, and the torsion angle is
       going to be undefined.  The easiest check for this problem is
       to use the product of the two lengths.
    */
    if (rA * rB < OpenMD::epsilon) return;
    
    A.normalize();
    B.normalize();  
    
    //  Calculate the sin and cos
    RealType cos_phi = dot(A, B) ;
    if (cos_phi > 1.0) cos_phi = 1.0;
    if (cos_phi < -1.0) cos_phi = -1.0; 
    
    RealType dVdcosPhi;
    torsionType_->calcForce(cos_phi, potential_, dVdcosPhi);
    Vector3d f1 ;
    Vector3d f2 ;
    Vector3d f3 ;
    
    Vector3d dcosdA = (cos_phi * A - B) /rA;
    Vector3d dcosdB = (cos_phi * B - A) /rB;
    
    f1 = dVdcosPhi * cross(r32, dcosdA);
    f2 = dVdcosPhi * ( cross(r43, dcosdB) - cross(r21, dcosdA));
    f3 = dVdcosPhi * cross(dcosdB, r32);
    
    atoms_[0]->addFrc(f1);
    atoms_[1]->addFrc(f2 - f1);
    atoms_[2]->addFrc(f3 - f2);
    atoms_[3]->addFrc(-f3);
    
    if (doParticlePot) {
      atoms_[0]->addParticlePot(potential_);
      atoms_[1]->addParticlePot(potential_);
      atoms_[2]->addParticlePot(potential_);
      atoms_[3]->addParticlePot(potential_);
    }
    
    angle = acos(cos_phi) /M_PI * 180.0;    
  }  