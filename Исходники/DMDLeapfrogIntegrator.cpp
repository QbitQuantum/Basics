void DMDLeapfrogIntegrator::calculateDissipativeAndRandomForces() {
  Real sdv = 1;
  myRandomForces->zero();
  myDissipativeForces->zero();
  for (unsigned int i = 0; i < app->topology->angles.size(); i++) {
    int a1 = app->topology->angles[i].atom1;
    int a2 = app->topology->angles[i].atom2;
    int a3 = app->topology->angles[i].atom3;

    const Vector3D &posi1 = app->positions[a1];
    const Vector3D &posi2 = app->positions[a2];
    const Vector3D &posi3 = app->positions[a3];
    const Vector3D &vel1 = app->velocities[a1];
    const Vector3D &vel2 = app->velocities[a2];
    const Vector3D &vel3 = app->velocities[a3];

    //now handle atoms 1 and 2
    Vector3D unitVec = posi2 - posi1;   // now it is only a vector
    unitVec.normalize();
    // now the vector is unit vector, the dist is the length of the original
    // vector. We assume the weight, w1, and w2 to be 1 always, thus the 
    // following still holds true
    // w1 = w2^2;

    Real coeff = -myGamma * ((vel2 - vel1).dot(unitVec));
    (*myDissipativeForces)[a2] += unitVec * coeff;
    (*myDissipativeForces)[a1] -= unitVec * coeff;
    Real randNum = randomGaussian(sdv, mySeed);
    coeff = mySigma * randNum;
    (*myRandomForces)[a2] += unitVec * coeff;
    (*myRandomForces)[a1] -= unitVec * coeff;

    //now handle atoms 2 and 3
    unitVec = posi3 - posi2;   // now it is only a vector
    unitVec.normalize();

    coeff = -myGamma * ((vel3 - vel2).dot(unitVec));
    (*myDissipativeForces)[a3] += unitVec * coeff;
    (*myDissipativeForces)[a2] -= unitVec * coeff;
    randNum = randomGaussian(sdv, mySeed);
    coeff = mySigma * randNum;
    (*myRandomForces)[a3] += unitVec * coeff;
    (*myRandomForces)[a2] -= unitVec * coeff;

    //now handle atoms 1 and 3
    unitVec = posi3 - posi1;   // now it is only a vector
    unitVec.normalize();

    coeff = -myGamma * ((vel3 - vel1).dot(unitVec));
    (*myDissipativeForces)[a3] += unitVec * coeff;
    (*myDissipativeForces)[a1] -= unitVec * coeff;
    randNum = randomGaussian(sdv, mySeed);
    coeff = mySigma * randNum;
    (*myRandomForces)[a3] += unitVec * coeff;
    (*myRandomForces)[a1] -= unitVec * coeff;
  }
}