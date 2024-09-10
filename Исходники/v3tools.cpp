//make basis ortonormal again.
void ortoNormalize(V3f & nnx, V3f & nny, V3f & nnz){
  V3f newy; newy.cross(nnz, nnx);
  V3f newz; newz.cross(nnx, newy);
  newy /= newy.length();
  newz /= newz.length();
  nnx /= nnx.length();
  nny = newy;
  nnz = newz;
};