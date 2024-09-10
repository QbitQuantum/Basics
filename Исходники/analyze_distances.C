double getSimilarity(const alignment& A,int s1,int s2) {
  int match=0;
  int total=0;
  for(int column=0;column<A.length();column++) {
    if (A.gap(column,s1) or A.gap(column,s2)) continue;
    total++;

    if (A(column,s1) == A(column,s2))
      match++;
  }
  return double(match)/total;
}