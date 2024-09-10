  /**
   * Animate the cube rotations.
   * @param elapsed The elapsed time since the last draw call.
   */
  mat4 Cubie::animateCubeRotation(double elapsed)
  {
    float cosTheta;

    // Spherical linear interpolation (SLERP) between the current and desired
    // orientations.  The orientation needs to be normalized or precision
    // will be lost over time, causing constantly animated cubes.
    this->cubeRot.orientation = normalize(slerp(this->cubeRot.orientation,
      this->cubeRot.desired, this->cubeRot.speed * (float)elapsed));

    // The cosine between the orientation and desired.
    cosTheta = dot(this->cubeRot.orientation, this->cubeRot.desired);

    //if (cosTheta > .999 && cosTheta < 1.001 || cosTheta)
    if (fabs(1 - fabs(cosTheta)) < .00001)
      this->cubeRot.orientation = this->cubeRot.desired;

    return mat4_cast(this->cubeRot.orientation);
  }