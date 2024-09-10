Vector2F MutableMatrix44D::project(const Vector3F& point,
                                   const int vpLeft,
                                   const int vpTop,
                                   const int vpWidth,
                                   const int vpHeight) const {
  const float x = point._x;
  const float y = point._y;
  const float z = point._z;
  //  const float w = 1.0;

  //Transformating point
  float out0 = (float) _m00 * x + (float) _m01 * y + (float) _m02 * z + (float) _m03 /* * w */;
  float out1 = (float) _m10 * x + (float) _m11 * y + (float) _m12 * z + (float) _m13 /* * w */;
  //float out2 = _m20 * x + _m21 * y + _m22 * z + _m23 * w;
  const float out3 = (float) _m30 * x + (float) _m31 * y + (float) _m32 * z + (float) _m33 /* * w */;

  if (out3 == 0.0) {
    return Vector2F::nan();
  }

  out0 /= out3;
  out1 /= out3;
  //out2 /= out3;

  const float winx = vpLeft + (1.0f + out0) * vpWidth / 2.0f;
  const float winy = vpTop  + (1.0f + out1) * vpHeight / 2.0f;
  //float winz = (1.0 + in2) / 2.0;
  return Vector2F(winx, winy);
}