float gauss3d(float dx, float dy, float dz, float s) {
  return expf(-(dx*dx + dy*dy + dz*dz)/(s*s));
}