float NoiseSampler::vnoise(const glm::vec3& p) {
  int ix = FLOOR(p[0]);
  int iy = FLOOR(p[1]);
  int iz = FLOOR(p[2]);
  float fy = p[1]-iy;
  float fx = p[0]-ix;
  float fz = p[2]-iz;

  float xp[4], yp[4], zp[4];

  for(int k = -1; k <= 2; k++) {
    for(int j = -1; j <= 2; j++) {
      for(int i = -1; i <= 2; i++) {
        xp[i+1] = m_value_table[INDEX_3(ix+i, iy+j, iz+k)];
      }
      yp[j+1] = catmull_rom4(fx, xp);
    }
    zp[k+1] = catmull_rom4(fy, yp);
  }
  return catmull_rom4(fz, zp);
}