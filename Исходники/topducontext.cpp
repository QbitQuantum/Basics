void removeFromVector(QVector<T>& vec, const T& t) {
  for(int a  =0; a < vec.size(); ++a) {
    if(vec[a] == t) {
      vec.remove(a);
      removeFromVector(vec, t);
      return;
    }
  }
}