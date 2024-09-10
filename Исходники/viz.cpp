void Viz::issueNormal(vector<GLfloat> &normal, vector<GLfloat> &vertices, vector<GLuint> &indices, double mult) {
  normal.clear();
  int mxId = 0;
  for (int i = 0; i < indices.size(); i++) 
    if (indices[i] > mxId)
      mxId = indices[i];

  vector<Vec3d> norms(mxId + 1);
  vector<int> count(mxId + 1);
  for (int i = 0; i < indices.size(); i+= 3) {
    unsigned int *p = &indices[i];
    Vec3d a(vertices[p[0] * 3], vertices[p[0] * 3 + 1], vertices[p[0] * 3 + 2]);
    Vec3d b(vertices[p[1] * 3], vertices[p[1] * 3 + 1], vertices[p[1] * 3 + 2]);
    Vec3d c(vertices[p[2] * 3], vertices[p[2] * 3 + 1], vertices[p[2] * 3 + 2]);
    Vec3d ab = b - a;
    Vec3d ac = c - a;
    Vec3d cp = ab.cross(ac);
    cp /= norm(cp);

    for (int j = 0; j < 3; j++) {
      //count[p[j]]++;
      //slerp(norms[p[j]], cp, norms[p[j]], 1.0 / count[p[j]]);
      norms[p[j]] += cp;
      count[p[j]] ++;
    }
  }
  for (int i = 0; i < norms.size(); i++) {
    norms[i] /= norm(norms[i]);
    norms[i] *= mult;
    normal.push_back(norms[i][0]);
    normal.push_back(norms[i][1]);
    normal.push_back(norms[i][2]);
  }
}