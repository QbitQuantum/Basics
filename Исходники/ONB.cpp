void ONB:: initFromUW(const Vec& u, const Vec& w){
  U = normalize(u);
  V = normalize(w.cross(U));
  W = U.cross(V);
}